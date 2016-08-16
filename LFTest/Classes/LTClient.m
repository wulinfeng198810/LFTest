//
//  LTClient.m
//  LTClient
//
//  Created by 吴林峰 on 16/8/4.
//  Copyright © 2016年 WiseUC. All rights reserved.
//

#import "LTClient.h"

#import "Macros.h"
#import "NetworkUtility.h"
#import "WiseUCHelper.h"
#import "HttpTool.h"
#import "IniHelper.h"

@implementation LTClient


+ (void)downloadIMServerCfgWithServerIP:(NSString *)ServerIP complete:(void(^)(NSDictionary *IMServerCfgDict))complete {
    
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

@end
