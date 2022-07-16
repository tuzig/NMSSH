#import "NMSSH.h"
#import "NMSSHChannelStream.h"
#import <pthread/pthread.h>

//#define pthread_mutex_lock(lock) NSLog(@"LOCK: %p", lock); pthread_mutex_lock(lock);

@class NMSSHSession;
@protocol NMSSHChannelDelegate;

typedef NS_ENUM(NSInteger, NMSSHChannelError) {
    NMSSHChannelExecutionError,
    NMSSHChannelExecutionResponseError,
    NMSSHChannelRequestPtyError,
    NMSSHChannelExecutionTimeout,
    NMSSHChannelAllocationError,
    NMSSHChannelRequestShellError,
    NMSSHChannelWriteError,
    NMSSHChannelReadError
};

typedef NS_ENUM(NSInteger, NMSSHChannelPtyTerminal) {
    NMSSHChannelPtyTerminalVanilla,
    NMSSHChannelPtyTerminalVT100,
    NMSSHChannelPtyTerminalVT102,
    NMSSHChannelPtyTerminalVT220,
    NMSSHChannelPtyTerminalAnsi,
    NMSSHChannelPtyTerminalXterm
};

typedef NS_ENUM(NSInteger, NMSSHChannelType)  {
    NMSSHChannelTypeClosed, // Channel = NULL
    NMSSHChannelTypeExec,
    NMSSHChannelTypeShell,
    NMSSHChannelTypeSCP,
    NMSSHChannelTypeSubsystem // Not supported by NMSSH framework
};

/**
 NMSSHChannel provides functionality to work with SSH shells and SCP.
 */
@interface NMSSHChannel : NSObject

/** A valid NMSSHSession instance */
@property (nonatomic, nonnull, readonly) NMSSHSession *session;

/** Size of the buffers used by the channel, defaults to 0x4000 */
@property (nonatomic, assign) NSUInteger bufferSize;

/// ----------------------------------------------------------------------------
/// @name Setting the Delegate
/// ----------------------------------------------------------------------------

/**
 The receiver’s `delegate`.

 You can use the `delegate` to receive asynchronous read from a shell.
 */
@property (nonatomic, nullable, weak) id<NMSSHChannelDelegate> delegate;

/// ----------------------------------------------------------------------------
/// @name Initializer
/// ----------------------------------------------------------------------------

/** Current channel type or `NMSSHChannelTypeClosed` if the channel is closed */
@property (nonatomic, readonly) NMSSHChannelType type;

- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 Create a new NMSSHChannel instance.

 @param session A valid, connected, NMSSHSession instance
 @returns New NMSSHChannel instance
 */
- (nonnull instancetype)initWithSession:(nonnull NMSSHSession *)session;

/// ----------------------------------------------------------------------------
/// @name Shell command execution
/// ----------------------------------------------------------------------------

/** The last response from a shell command execution */
@property (nonatomic, nullable, readonly) NSString *lastResponse;

/** Request a pseudo terminal before executing a command */
@property (nonatomic, assign) BOOL requestPty;

/** Terminal emulation mode if a PTY is requested, defaults to vanilla */
@property (nonatomic, assign) NMSSHChannelPtyTerminal ptyTerminalType;

/**
 Execute a shell command on the server.

 If an error occurs, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @returns Shell command response
 */
- (nonnull NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param timeout The time to wait (in seconds) before giving up on the request
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error timeout:(nonnull NSNumber *)timeout;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @param timeout The time to wait (in seconds) before giving up on the request
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out timeout:(nonnull NSNumber *)timeout;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @param exitCode Command exit code
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out exitCode: (NSNumber * _Nonnull * _Nonnull)exitCode;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @param exitSignal Command exit signal
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out exitSignal: (NSString * _Nullable * _Nullable)exitSignal;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell ßcript that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @param exitCode Command exit code
 @param exitSignal Command exit signal
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out exitCode: (NSNumber * _Nonnull * _Nonnull)exitCode exitSignal: (NSString * _Nonnull * _Nonnull)exitSignal;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @param exitCode Command exit code
 @param timeout The time to wait (in seconds) before giving up on the request
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out exitCode: (NSNumber * _Nonnull * _Nonnull)exitCode timeout:(nonnull NSNumber *)timeout;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @param exitSignal Command exit signal
 @param timeout The time to wait (in seconds) before giving up on the request
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out exitSignal: (NSString * _Nullable * _Nullable)exitSignal timeout:(nonnull NSNumber *)timeout;

/**
 Execute a shell command on the server with a given timeout.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param error Error handler
 @param stdout_out Stdout output
 @param stderr_out Stderr output
 @param exitCode Command exit code
 @param exitSignal Command exit signal
 @param timeout The time to wait (in seconds) before giving up on the request
 @returns Shell command response
 */
- (nullable NSString *)execute:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error stdout_out:(NSString * _Nullable * _Nullable)stdout_out stderr_out:(NSString * _Nullable * _Nullable)stderr_out exitCode: (NSNumber * _Nonnull * _Nonnull)exitCode exitSignal: (NSString * _Nullable * _Nullable)exitSignal timeout:(nonnull NSNumber *)timeout;

/**
 Execute a shell command on the server and stream output.

 If an error occurs or the connection timed out, it will return `nil` and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param command Any shell script that is available on the server
 @param channelStream Stream delegate
 */
- (void)executeStream:(nonnull NSString *)command channelStream: (nonnull NMSSHChannelStream*)channelStream;

/// ----------------------------------------------------------------------------
/// @name Remote shell session
/// ----------------------------------------------------------------------------

/** User-defined environment variables for the session, defaults to `nil` */
@property (nonatomic, nullable, strong) NSDictionary *environmentVariables;

/**
 Request a remote shell on the channel.

 If an error occurs, it will return NO and populate the error object.
 If requestPty is enabled request a pseudo terminal before running the
 command.

 @param error Error handler
 @returns Shell initialization success
 */
- (BOOL)startShell:(NSError * _Nullable * _Nullable)error;

/**
 Close a remote shell on an active channel.
 */
- (void)closeShell;

/**
 Close this channel.
 */
- (void)closeChannel;

/**
 Write a command on the remote shell.

 If an error occurs or the connection timed out, it will return NO and populate the error object.

 @param command Any command that is available on the server
 @param error Error handler
 @returns Shell write success
 */
- (BOOL)write:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error;

/**
 Write a command on the remote shell with a given timeout.

 If an error occurs or the connection timed out, it will return NO and populate the error object.

 @param command Any command that is available on the server
 @param error Error handler
 @param timeout The time to wait (in seconds) before giving up on the request
 @returns Shell write success
 */
- (BOOL)write:(nonnull NSString *)command error:(NSError * _Nullable * _Nullable)error timeout:(nonnull NSNumber *)timeout;

/**
 Write data on the remote shell.

 If an error occurs or the connection timed out, it will return NO and populate the error object.

 @param data Any data
 @param error Error handler
 @returns Shell write success
 */
- (BOOL)writeData:(nonnull NSData *)data error:(NSError * _Nullable * _Nullable)error;

/**
 Write data on the remote shell with a given timeout.

 If an error occurs or the connection timed out, it will return NO and populate the error object.

 @param data Any data
 @param error Error handler
 @param timeout The time to wait (in seconds) before giving up on the request
 @returns Shell write success
 */
- (BOOL)writeData:(nonnull NSData *)data error:(NSError * _Nullable * _Nullable)error timeout:(nonnull NSNumber *)timeout;

/**
 Request size for the remote pseudo terminal.

 This method should be called only after startShell:

 @param width Width in characters for terminal
 @param height Height in characters for terminal
 @returns Size change success
 */
- (BOOL)requestSizeWidth:(NSUInteger)width height:(NSUInteger)height;

/// ----------------------------------------------------------------------------
/// @name SCP file transfer
/// ----------------------------------------------------------------------------

/**
 Upload a local file to a remote server.

 If to: specifies a directory, the file name from the original file will be
 used.

 @param localPath Path to a file on the local computer
 @param remotePath Path to save the file to
 @returns SCP upload success
 */
- (BOOL)uploadFile:(nonnull NSString *)localPath to:(nonnull NSString *)remotePath;

/**
 Download a remote file to local the filesystem.

 If to: specifies a directory, the file name from the original file will be
 used.

 @param remotePath Path to a file on the remote server
 @param localPath Path to save the file to
 @returns SCP download success
 */
- (BOOL)downloadFile:(nonnull NSString *)remotePath to:(nonnull NSString *)localPath;

/**
 Download a remote file to local the filesystem.

 If to: specifies a directory, the file name from the original file will be
 used.

 @param remotePath Path to a file on the remote server
 @param localPath Path to save the file to
 @param progress Method called periodically with number of bytes downloaded and total file size.
        Returns NO to abort.
 @returns SCP download success
 */
- (BOOL)downloadFile:(nonnull NSString *)remotePath
                  to:(nonnull NSString *)localPath
            progress:(BOOL (^_Nullable)(NSUInteger, NSUInteger))progress;

/**
 Upload a local file to a remote server.

 If to: specifies a directory, the file name from the original file will be
 used.

 @param localPath Path to a file on the local computer
 @param remotePath Path to save the file to
 @param progress Method called periodically with number of bytes uploaded. Returns NO to abort.
 @returns SCP upload success
 */
- (BOOL)uploadFile:(nonnull NSString *)localPath
                to:(nonnull NSString *)remotePath
          progress:(BOOL (^_Nullable)(NSUInteger))progress;


@end
