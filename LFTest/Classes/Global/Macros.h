//
//  Macros.h
//

//全局唯一的window
#define KEY_WINDOW  [[UIApplication sharedApplication] keyWindow]

//动态获取设备高度
#define SCREEN_HEIGHT [UIScreen mainScreen].bounds.size.height
//动态获取设备宽度
#define SCREEN_WIDTH [UIScreen mainScreen].bounds.size.width

#define IPHONE_HEIGHT [UIScreen mainScreen].bounds.size.height
#define IPHONE_WIDTH [UIScreen mainScreen].bounds.size.width



#pragma mark - =================== 颜色 ========================

//设置颜色
#define HEXCOLOR(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

//设置颜色与透明度
#define HEXCOLORAL(rgbValue, al) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:al]

#define COMMENT_COLOR [UIColor colorWithRed:69/255.f green:161/255.f blue:193/255.f alpha:1.0f]

#define DarkGreenShemeColor HEXCOLOR(0x107d22)
#define DarkBlueShemeColor HEXCOLOR(0x154d98)

#pragma mark - =================== 文件路径 ========================

#pragma  mark  --语音文件路径
#define kVoiceFilePath   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/Voice"]

#pragma  mark  --图片文件路径
#define kPictureFilePath   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/Pictures"]

#pragma  mark  --文件路径
#define kFilePath   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/File"]

#pragma  mark  --数据库路径
#define kSqlitePath   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/WiseucSqlite"]

#pragma  mark  --头像缓存路径
#define kHeadPicture   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/HeadPicture"]

#pragma  mark  --组织架构文件路径
#define kOrgFilePath   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/OrgFilePath"]

#pragma  mark  --ftp配置文件路径
#define kFtpConfigFile   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/FtpConfigFile"]

#pragma  mark  --消息漫游文件
#define kRoamingMsgCacheFile   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingString:@"/wiseuc/RoamingMsgCacheFile/RoamingMsgCacheFile.plist"]


#pragma mark - =================== 共享 ========================

#define kKEYCODE @"gzRN53VWRF9BYUXo"
#define Wiseuc_SingleChatHeadPicture  @"singleChat_online"
