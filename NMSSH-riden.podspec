Pod::Spec.new do |spec|
  spec.name         = "NMSSH-riden"
  spec.version      = "2.6.2"
  spec.summary      = "NMSSH is a clean, easy-to-use, unit tested framework for iOS and OSX that wraps libssh2."
  spec.homepage     = "https://github.com/ridenui/NMSSH"
  spec.license      = 'MIT'
  spec.authors      = { "Christoffer Lejdborg" => "hello@9muses.se", "Tommaso Madonia" => "tommaso@madonia.me", "Nils Bergmann" => "nilsbergmann@noim.io" }

  spec.source       = { :git => "https://github.com/ridenui/NMSSH.git", :tag => spec.version.to_s }

  spec.requires_arc = true
  spec.platform = :ios
  spec.platform = :osx

  spec.source_files = 'NMSSH', 'NMSSH/**/*.{h,m}'
  spec.public_header_files  = 'NMSSH/*.h', 'NMSSH/Protocols/*.h', 'NMSSH/Config/NMSSHLogger.h'
  spec.private_header_files = 'NMSSH/Config/NMSSH+Protected.h', 'NMSSH/Config/socket_helper.h'
  spec.libraries    = 'z'
  spec.framework    = 'CFNetwork'

  spec.ios.deployment_target  = '9.0'
  spec.ios.vendored_libraries = 'NMSSH-iOS/Libraries/lib/libssh2.a', 'NMSSH-iOS/Libraries/lib/libssl.a', 'NMSSH-iOS/Libraries/lib/libcrypto.a'
  spec.ios.source_files       = 'NMSSH-iOS', 'NMSSH-iOS/Libraries/**/*.h'
  spec.ios.public_header_files  = 'NMSSH-iOS/Libraries/**/*.h'

  spec.osx.deployment_target  = '10.15.0'
  spec.osx.vendored_libraries = 'NMSSH-OSX/Libraries/lib/libssh2.a', 'NMSSH-OSX/Libraries/lib/libssl.a', 'NMSSH-OSX/Libraries/lib/libcrypto.a'
  spec.osx.source_files       = 'NMSSH-OSX', 'NMSSH-OSX/Libraries/**/*.h'
  spec.osx.public_header_files  = 'NMSSH-OSX/Libraries/**/*.h'

  spec.xcconfig = {
    "OTHER_LDFLAGS" => "-ObjC",
  }

  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64', "DEFINES_MODULE" => "YES" }
  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
end
