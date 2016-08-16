//
//  HttpTool.m
//  02-文件上传下载工具抽取
//
//  Created by Vincent_Guo on 14-6-9.
//  Copyright (c) 2014年 itcast. All rights reserved.
//

#import "HttpTool.h"
#import "Encrypt_Decipher.h"
#import "Macros.h"

#import <AFNetworking/AFNetworking.h>

#define kTimeOut 1.0

@interface HttpTool()
{
    //下载
    ProgressBlock _dowloadProgressBlock;
    CompletionBlock _downladCompletionBlock;
    NSString *_savePath;
    
    
    //上传
    ProgressBlock _uploadProgressBlock;
    CompletionBlock _uploadCompletionBlock;
    
    NSURLSessionDownloadTask *_downloadTask;
}

@end


@implementation HttpTool

#pragma mark - 下载

-(void)downLoadFromURL:(NSURL *)url
              savePath:(NSString *)savePath
         progressBlock:(ProgressBlock)progressBlock
            completion:(CompletionBlock)completionBlock {
    
    if ( !url ) {
        return;
    }
    
    __block ProgressBlock dowloadProgressBlock = [progressBlock copy];
    __block CompletionBlock downladCompletionBlock = [completionBlock copy];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ( [fileManager fileExistsAtPath:savePath] ) {
        if ( downladCompletionBlock ) {
            downladCompletionBlock(@"Download Successed!", nil);
        }
        return;
    }
    
    NSURLRequest *request = [NSURLRequest requestWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:5];
    
    AFHTTPSessionManager *afManager = [AFHTTPSessionManager manager];
    afManager.requestSerializer = [AFHTTPRequestSerializer serializer];
    afManager.responseSerializer = [AFHTTPResponseSerializer serializer];
    
    _downloadTask  = [afManager downloadTaskWithRequest:request progress:^(NSProgress * _Nonnull downloadProgress) {
        if ( dowloadProgressBlock ) {
            CGFloat progress = downloadProgress.completedUnitCount / downloadProgress.totalUnitCount;
            dowloadProgressBlock(progress);
        }
    } destination:^NSURL * _Nonnull(NSURL * _Nonnull targetPath, NSURLResponse * _Nonnull response) {

        NSError *error = nil;
        if(![fileManager fileExistsAtPath:[savePath stringByDeletingLastPathComponent]]){
            [fileManager createDirectoryAtPath:[savePath stringByDeletingLastPathComponent]
                   withIntermediateDirectories:YES
                                    attributes:nil
                                         error:&error];
        }
        return [NSURL fileURLWithPath:savePath];
    } completionHandler:^(NSURLResponse * _Nonnull response, NSURL * _Nullable filePath, NSError * _Nullable error) {
        
        if ( !downladCompletionBlock ) {
            return;
        }
        if ( !error  ) {
            downladCompletionBlock(@"Download Successed!", nil);
        } else {
            NSFileManager *fileManager = [NSFileManager defaultManager];
            [fileManager removeItemAtPath:savePath error:nil];
            
            downladCompletionBlock(nil, error);
        }
    }];
    
    [_downloadTask resume];
}

- (void)cancel
{
    if ( _downloadTask ) {
        [_downloadTask cancel];
        _downloadTask = nil;
    }
}


#pragma mark - 表单上传

- (void)FORM_UploadFile:(NSString *)localPath
        targetServerURL:(NSString *)serverURL
      requireEncryption:(BOOL)requireEncryption
          progressBlock:(ProgressBlock)progressBlock
             completion:(CompletionBlock)completionBlock
{
    NSURL *url = [NSURL URLWithString:serverURL];
    __block CompletionBlock uploadCompletionBlock = [completionBlock copy];
    __block ProgressBlock uploadProgressBlock = [progressBlock copy];
    
    NSDictionary *params = @{@"userName"     : @"rob",
                             @"userEmail"    : @"rob@email.com",
                             @"userPassword" : @"password"};
    
    NSString *boundary = [self generateBoundaryString];
    
    // configure the request
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:url];
    [request setHTTPMethod:@"POST"];
    
    // set content type
    
    NSString *contentType = [NSString stringWithFormat:@"multipart/form-data; boundary=%@", boundary];
    [request setValue:contentType forHTTPHeaderField: @"Content-Type"];
    
    NSData *httpBody = [self createBodyWithBoundary:boundary
                                         parameters:params
                                              paths:@[localPath]
                                          fieldName:@"uploadFile"
                                  requireEncryption:requireEncryption];
    
    AFHTTPSessionManager *afManager = [AFHTTPSessionManager manager];
    afManager.requestSerializer = [AFHTTPRequestSerializer serializer];
    afManager.responseSerializer = [AFHTTPResponseSerializer serializer];
    
    [[afManager uploadTaskWithRequest:request fromData:httpBody progress:^(NSProgress * _Nonnull uploadProgress) {
        
        if ( uploadProgressBlock ) {
            float progress = (float) uploadProgress.completedUnitCount / uploadProgress.totalUnitCount;
            uploadProgressBlock(progress);
        }
        
    } completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        
        if ( uploadCompletionBlock ) {
            uploadCompletionBlock(responseObject, error);
        }
        
    }] resume];
}

- (NSData *)createBodyWithBoundary:(NSString *)boundary
                        parameters:(NSDictionary *)parameters
                             paths:(NSArray *)paths
                         fieldName:(NSString *)fieldName
                 requireEncryption:(BOOL)requireEncryption
{
    NSMutableData *httpBody = [NSMutableData data];
    
    // add params (all params are strings)
    
    [parameters enumerateKeysAndObjectsUsingBlock:^(NSString *parameterKey, NSString *parameterValue, BOOL *stop) {
        [httpBody appendData:[[NSString stringWithFormat:@"--%@\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"%@\"\r\n\r\n", parameterKey] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"%@\r\n", parameterValue] dataUsingEncoding:NSUTF8StringEncoding]];
    }];
    
    // add image data
    
    for (NSString *path in paths) {
        NSString *filename  = [path lastPathComponent];
        
        NSData   *data      = [NSData dataWithContentsOfFile:path];
        NSString *mimetype  = [self mimeTypeForPath:path];
        
        [httpBody appendData:[[NSString stringWithFormat:@"--%@\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"%@\"; filename=\"%@\"\r\n", fieldName, filename] dataUsingEncoding:NSUTF8StringEncoding]];
        [httpBody appendData:[[NSString stringWithFormat:@"Content-Type: %@\r\n\r\n", mimetype] dataUsingEncoding:NSUTF8StringEncoding]];

        [httpBody appendData:data];
        
        //图片上传加密
        if ( requireEncryption ) {
            [httpBody appendData:[@"\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
            [httpBody appendData:[[self encodingFileName:filename] dataUsingEncoding:NSUTF8StringEncoding]];
        }

        
        [httpBody appendData:[@"\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    [httpBody appendData:[[NSString stringWithFormat:@"--%@--\r\n", boundary] dataUsingEncoding:NSUTF8StringEncoding]];
    
    return httpBody;
}

- (NSString *)mimeTypeForPath:(NSString *)path
{
    
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL fileURLWithPath:path]];
    
    NSError *error;
    NSURLResponse*response;
    
    [NSURLConnection sendSynchronousRequest:request
                          returningResponse:&response
                                      error:&error];
    return [response MIMEType];
}

- (NSString *)generateBoundaryString
{
    return [NSString stringWithFormat:@"Boundary-%@", [[NSUUID UUID] UUIDString]];
}

- (NSString *)encodingFileName:(NSString *)fileName
{
    NSString *imageNameEncoding  = [Base64 encodeWithString:fileName];
    imageNameEncoding = [imageNameEncoding stringByAppendingString:@"wisucuppicture"];
    imageNameEncoding = [[imageNameEncoding md5] lowercaseString];
    return imageNameEncoding;
}

@end
