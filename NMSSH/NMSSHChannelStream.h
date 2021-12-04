//
//  NMSSHChannelStream.h
//  NMSSH
//
//  Created by Nils Bergmann on 04/12/2021.
//

#ifndef NMSSHChannelStream_h
#define NMSSHChannelStream_h

@protocol NMSSHChannelStreamReceiveDelegate <NSObject>

-(void)onStdout: (NSString *)stringText;

-(void)onStderr: (NSString *)stringText;

-(void)onExit: (NSNumber *)exitCode;

-(void)onError: (NSError *)error;

@end

@interface NMSSHChannelStream : NSObject

@property (nonatomic,strong) id <NMSSHChannelStreamReceiveDelegate>delegate;

@end

#endif /* NMSSHChannelStream_h */
