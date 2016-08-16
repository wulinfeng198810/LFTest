//
//  IniHelper.m
//  WiseUC
//
//  Created by 吴林峰 on 16/1/25.
//  Copyright © 2016年 WiseUC. All rights reserved.
//

#import "IniHelper.h"
#import "SimpleIni.h"
#import "Base64.h"
@implementation IniHelper

+ (NSDictionary *)parseIniFile:(NSString *)savePath pragram:(NSDictionary *)dict {
    
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile([savePath UTF8String]);
    // 离线文件
    const char * cFileArkServerIP = ini.GetValue("OffFileServer", "OffFileServerIP");
    const char * cFileArkServerPort = ini.GetValue("OffFileServer", "OffFileServerPort");

    // 登录方式
    const char * cLDAPAuthEnable = ini.GetValue("LDAP", "LDAPAuthEnable");
    const char * cMD5Enable = ini.GetValue("MD5Login", "MD5Enable");
    
    // 消息漫游服务器
    const char * cMsgServerConnAddr = ini.GetValue("MsgServer", "connAddr");
    
    if ( !cFileArkServerIP || !cFileArkServerPort || !cLDAPAuthEnable || !cMD5Enable ) {
        return nil;
    }
    
    NSString *FileArkServerIP = [NSString stringWithCString:cFileArkServerIP encoding:NSUTF8StringEncoding];
    NSString *FileArkServerPort = [NSString stringWithCString:cFileArkServerPort encoding:NSUTF8StringEncoding];
    
    NSString *LDAPAuthEnable = [NSString stringWithCString:cLDAPAuthEnable encoding:NSUTF8StringEncoding];
    NSString *MD5Enable = [NSString stringWithCString:cMD5Enable encoding:NSUTF8StringEncoding];
    
    NSString *ftpURLServerConfig = [NSString stringWithFormat:@"%@:%@",FileArkServerIP,FileArkServerPort];
    
    NSMutableDictionary *mDict = [NSMutableDictionary dictionaryWithDictionary:@{kLDAPAuthEnable:@([LDAPAuthEnable boolValue]),
                                                                                 kMD5Enable:@([MD5Enable boolValue]),
                                                                                 kFtpURLServerConfig:ftpURLServerConfig}];
    if ( cMsgServerConnAddr ) {
        NSString *MsgServerConnAddr = [NSString stringWithCString:cMsgServerConnAddr encoding:NSUTF8StringEncoding];
        MsgServerConnAddr = [Base64 decodeBase64String:MsgServerConnAddr];
        if ( [MsgServerConnAddr hasPrefix:@"tcp"] ) {
            [mDict setValue:MsgServerConnAddr forKey:kMsgServerConnAddr];
        }
    }
    
    return mDict;
}

@end
