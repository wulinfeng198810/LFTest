/*!
 *  \~chinese
 *  @header LTErrorCode.h
 *  @abstract SDK定义的错误类型
 *
 *  \~english
 *  @header LTErrorCode.h
 *  @abstract SDK defined error type
 */

typedef enum{
    
    LTErrorGeneral = 1,                      /*! \~chinese 一般错误 \~english General error */
    LTErrorNetworkUnavailable,               /*! \~chinese 网络不可用 \~english Network is unavaliable */
    
    LTErrorInvalidAppkey = 100,              /*! \~chinese Appkey无效 \~english App key is invalid */
    LTErrorInvalidUsername,                  /*! \~chinese 用户名无效 \~english User name is invalid */
    LTErrorInvalidPassword,                  /*! \~chinese 密码无效 \~english Password is invalid */
    LTErrorInvalidURL,                       /*! \~chinese URL无效 \~english URL is invalid */
    
    LTErrorUserAlreadyLogin = 200,           /*! \~chinese 用户已登录 \~english User has already logged in */
    LTErrorUserNotLogin,                     /*! \~chinese 用户未登录 \~english User has not logged in */
    LTErrorUserAuthenticationFailed,         /*! \~chinese 密码验证失败 \~english Password check failed */
    LTErrorUserAlreadyExist,                 /*! \~chinese 用户已存在 \~english User has already exist */
    LTErrorUserNotFound,                     /*! \~chinese 用户不存在 \~english User was not found */
    LTErrorUserIllegalArgument,              /*! \~chinese 参数不合法 \~english Illegal argument */
    LTErrorUserLoginOnAnotherDevice,         /*! \~chinese 当前用户在另一台设备上登录 \~english User has logged in from another device */
    LTErrorUserRLToved,                      /*! \~chinese 当前用户从服务器端被删掉 \~english User was rLToved from server */
    LTErrorUserRegisterFailed,               /*! \~chinese 用户注册失败 \~english Register user failed */
    LTErrorUpdateApnsConfigsFailed,          /*! \~chinese 更新推送设置失败 \~english Update apns configs failed */
    LTErrorUserPermissionDenied,             /*! \~chinese 用户没有权限做该操作 \~english User has no right for this operation. */
    
    LTErrorServerNotReachable = 300,         /*! \~chinese 服务器未连接 \~english Server is not reachable */
    LTErrorServerTimeout,                    /*! \~chinese 服务器超时 \~english Wait server response timeout */
    LTErrorServerBusy,                       /*! \~chinese 服务器忙碌 \~english Server is busy */
    LTErrorServerUnknownError,               /*! \~chinese 未知服务器错误 \~english Unknown server error */
    LTErrorServerGetDNSConfigFailed,         /*! \~chinese 获取DNS设置失败 \~english Get DNS config failed */
    
    LTErrorFileNotFound = 400,               /*! \~chinese 文件没有找到 \~english Can't find the file */
    LTErrorFileInvalid,                      /*! \~chinese 文件无效 \~english File is invalid */
    LTErrorFileUploadFailed,                 /*! \~chinese 上传文件失败 \~english Upload file failed */
    LTErrorFileDownloadFailed,               /*! \~chinese 下载文件失败 \~english Download file failed */
    
    LTErrorMessageInvalid = 500,             /*! \~chinese 消息无效 \~english Message is invalid */
    LTErrorMessageIncludeIllegalContent,      /*! \~chinese 消息内容包含不合法信息 \~english Message contains illegal content */
    LTErrorMessageTrafficLimit,              /*! \~chinese 单位时间发送消息超过上限 \~english Unit time to send messages over the upper limit */
    LTErrorMessageEncryption,                /*! \~chinese 加密错误 \~english Encryption error */
    
    LTErrorGroupInvalidId = 600,             /*! \~chinese 群组ID无效 \~english Group Id is invalid */
    LTErrorGroupAlreadyJoined,               /*! \~chinese 已加入群组 \~english User has already joined the group */
    LTErrorGroupNotJoined,                   /*! \~chinese 未加入群组 \~english User has not joined the group */
    LTErrorGroupPermissionDenied,            /*! \~chinese 没有权限进行该操作 \~english User has NO authority for the operation */
    LTErrorGroupMLTbersFull,                 /*! \~chinese 群成员个数已达到上限 \~english Reach group's max mLTber count */
    LTErrorGroupNotExist,                    /*! \~chinese 群组不存在 \~english Group is not exist */
    
    LTErrorChatroomInvalidId = 700,          /*! \~chinese 聊天室ID无效 \~english Chatroom id is invalid */
    LTErrorChatroomAlreadyJoined,            /*! \~chinese 已加入聊天室 \~english User has already joined the chatroom */
    LTErrorChatroomNotJoined,                /*! \~chinese 未加入聊天室 \~english User has not joined the chatroom */
    LTErrorChatroomPermissionDenied,         /*! \~chinese 没有权限进行该操作 \~english User has NO authority for the operation */
    LTErrorChatroomMLTbersFull,              /*! \~chinese 聊天室成员个数达到上限 \~english Reach chatroom's max mLTber count */
    LTErrorChatroomNotExist,                 /*! \~chinese 聊天室不存在 \~english Chatroom is not exist */
    
    LTErrorCallInvalidId = 800,              /*! \~chinese 实时通话ID无效 \~english Call id is invalid */
    LTErrorCallBusy,                         /*! \~chinese 已经在进行实时通话了 \~english User is busy */
    LTErrorCallRLToteOffline,                /*! \~chinese 对方不在线 \~english Callee is offline */
    LTErrorCallConnectFailed,                /*! \~chinese 实时通话建立连接失败 \~english Establish connection failed */
    
} LTErrorCode;
