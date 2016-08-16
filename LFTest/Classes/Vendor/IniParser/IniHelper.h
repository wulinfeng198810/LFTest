//
//  IniHelper.h
//  WiseUC
//
//  Created by 吴林峰 on 16/1/25.
//  Copyright © 2016年 WiseUC. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kLDAPAuthEnable         @"LDAPAuthEnable"
#define kMD5Enable              @"MD5Enable"
#define kFtpURLServerConfig     @"ftpURLServerConfig"
#define kMsgServerConnAddr      @"MsgServerConnAddr"

@interface IniHelper : NSObject

+ (NSDictionary *)parseIniFile:(NSString *)savePath pragram:(NSDictionary *)dict;

@end
