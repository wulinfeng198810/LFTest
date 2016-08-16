//
//  WiseUCHelper.m
//  XMPP即时通讯
//
//  Created by 吴林峰 on 15/10/21.
//  Copyright © 2015年 ___LinFeng___. All rights reserved.
//

#import "WiseUCHelper.h"

#import <UIKit/UIDevice.h>

#include <ifaddrs.h>
#include <arpa/inet.h>

#import "Macros.h"
#import "HttpTool.h"
//#import "UserManager.h"
#import "IniHelper.h"
#import "NetworkUtility.h"

@implementation WiseUCHelper


#pragma mark - public

+ (NSString *)deviceIPAdress {
    NSString *address = @"an error occurred when obtaining ip address";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    
    success = getifaddrs(&interfaces);
    
    if (success == 0) { // 0 表示获取成功
        
        temp_addr = interfaces;
        while (temp_addr != NULL) {
            if( temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if ([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
                else
                {
                    // 找不到就返回 0.0.0.0
                    address = @"0.0.0.0";
                }
            }
            
            temp_addr = temp_addr->ifa_next;
        }
    }
    
    freeifaddrs(interfaces);
    
    NSLog(@"手机的IP是：%@", address);
    
    return address;
}

+ (NSString *)getIOSVersion
{
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    return [NSString stringWithFormat:@"%.1f",version];
}

+ (NSString *)applicationVersion
{
    return [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
}

+ (NSString *)applicationDisplayName
{
    return [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleDisplayName"];
}

+ (NSString *)get_128Bytes_UUID
{
    return [[[self class] uuid] stringByReplacingOccurrencesOfString:@"-" withString:@""];
}

+ (NSString *)get_32Bytes_UUID
{

    NSString *uuid = [[[NSUUID UUID] UUIDString] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    
    return uuid;
}

+ (CGSize)getNSStringSize:(NSString *)str withFontSize:(CGFloat)fontSize forWidth:(CGFloat)width
{
    NSDictionary *dict = [NSDictionary dictionaryWithObject:[UIFont systemFontOfSize:fontSize] forKey:NSFontAttributeName];
    CGRect rect = [str boundingRectWithSize:CGSizeMake(width, 1000)
                                    options:NSStringDrawingUsesLineFragmentOrigin
                                 attributes:dict
                                    context:nil];
    return rect.size;
}

+ (void)clearCacheAction:(void(^)(BOOL clearFinished))complete{
    dispatch_async(
                   dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)
                   , ^{
                       NSString *cachPath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
                       
                       NSArray *files = [[NSFileManager defaultManager] subpathsAtPath:cachPath];
                       NSLog(@"files :%lu",(unsigned long)[files count]);
                       
                       BOOL ret = YES;
                       for (NSString *p in files) {
                           NSError *error;
                           NSString *path = [cachPath stringByAppendingPathComponent:p];
                           if ([[NSFileManager defaultManager] fileExistsAtPath:path]) {
                               ret = [[NSFileManager defaultManager] removeItemAtPath:path error:&error];
                           }
                       }
                       complete(ret);
                   });
}

+ (CGFloat)cacheSize {
    //获取缓存大小。。
    NSString *cachPath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    return [[self class] folderSizeAtPath:cachPath];
}

+ (void)downloadIMServerCfgWithServerIP:(NSString *)ServerIP complete:(void(^)(NSDictionary *IMServerCfgDict))complete
{
    // 外网登录配置文件地址
    NSString *ftpCfgFilePath1 = [NSString stringWithFormat:@"http://%@:14132/update/IMServerCfgWlan.inf",ServerIP];
    
    // 内网登录配置文件地址
    NSString *ftpCfgFilePath2 = [NSString stringWithFormat:@"http://%@:14132/update/IMServerCfg.inf",ServerIP];
    
    NSString *savePath = [kFtpConfigFile stringByAppendingPathComponent:@"IMServerCfg.inf"];
    
    void (^ TempBlock)(NSDictionary *IMServerCfgDict) = ^(NSDictionary *IMServerCfgDict) {
        if ( complete ) {
//            [UserManager shareInstance].ftpConfig = IMServerCfgDict[kFtpURLServerConfig];
//            [UserManager shareInstance].MsgServerConnAddr = IMServerCfgDict[kMsgServerConnAddr];
            complete(IMServerCfgDict);
        }
    };
    
    NSString *ftpCfgFilePath = nil;
    NetworkType networkType = [NetworkUtility checkIpValid:ServerIP];
    if ( networkType == NetworkType_ExtraIp ) {
        ftpCfgFilePath = ftpCfgFilePath1;
    }
    else if ( networkType == NetworkType_InnerIp ) {
        ftpCfgFilePath = ftpCfgFilePath2;
    }
    else {
        if ( complete ) {
            complete(nil);
        }
    }
    
    HttpTool *httpTool = [[HttpTool alloc] init];
    [[NSFileManager defaultManager] removeItemAtPath:savePath error:nil];
    [httpTool downLoadFromURL:[NSURL URLWithString:ftpCfgFilePath] savePath:savePath progressBlock:nil completion:^(id data, NSError *error) {
        
        if ( data ) {
            NSDictionary *IMServerCfgDict = [self parseIniFile:savePath pragram:nil];
            if ( IMServerCfgDict ) {
                TempBlock(IMServerCfgDict);
                return;
            }
        } else {
            if ( complete ) {
                complete(nil);
            }
        }
    }];
}

+ (NSDictionary *)parseIniFile:(NSString *)iniFilePath pragram:(NSDictionary *)pragram
{
    return [IniHelper parseIniFile:iniFilePath pragram:pragram];
}

#pragma mark - private

+ (NSString *)uuid
{
    return [[NSUUID UUID] UUIDString];
}

+ (CGFloat)folderSizeAtPath:(NSString *)folderPath
{
    NSFileManager *manager = [NSFileManager defaultManager];
    if (![manager fileExistsAtPath:folderPath]) {
        return 0;
    }
    
    NSEnumerator *childFilesEnumerator = [[manager subpathsAtPath:folderPath] objectEnumerator];
    
    NSString *fileName = nil;
    long long folderSize = 0;
    while ((fileName = [childFilesEnumerator nextObject]) != nil) {
        NSString *fileAbsolutePath = [folderPath stringByAppendingPathComponent:fileName];
        folderSize += [[self class] fileSizeAtPath:fileAbsolutePath];
    }
    return folderSize/(1024.0*1024.0);
}

+ (long long)fileSizeAtPath:(NSString *)filePath
{
    NSFileManager* manager = [NSFileManager defaultManager];
    if ([manager fileExistsAtPath:filePath]){
        return [[manager attributesOfItemAtPath:filePath error:nil] fileSize];
    }
    return 0;
}

@end
