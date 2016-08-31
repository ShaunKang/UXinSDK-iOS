Pod::Spec.new do |s|
  s.name         = "UXinSDK"
  s.version      = "1.8.0"
  s.summary      = "Let your app easily achieve in-app call. Learn more at http://yuantongxun.com."
  s.homepage     = "http://yuantongxun.com/"
  s.license      = {
      :type => 'Commercial',
      :text => <<-LICENSE
                Copyright (C) 2016 uxin.com.
                Permission is hereby granted to use this library as is, modification are not allowed.
                All rights reserved.
        
        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
        THE SOFTWARE.
      LICENSE
    }
  s.author              = { "UXinSDK" => "shaun.kang@uxin.com" }
  s.platform            = :ios, '6.0'
  s.source              = { :git => "https://github.com/ShaunKang/UXinSDK-iOS.git", :tag => s.version.to_s }
  s.source_files        = "*.h"
  s.public_header_files = "*.h"
  s.vendored_libraries  = "*.a"
  s.resource            = "*.bundle"
  s.frameworks          = 'AddressBook', 'MediaPlayer', 'CoreTelephony', 'MobileCoreServices', 'CFNetwork', 'SystemConfiguration', 'AudioToolbox', 'AVFoundation'
  s.ios.library         = 'sqlite3', 'c++', 'stdc++', 'z.1.2.5', 'stdc++.6'
  s.xcconfig            =  { 'LIRBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/UXinSDK/"', 'OTHER_LDFLAGS' => '-ObjC' ,'ENABLE_BITCODE' => 'NO'}
  s.requires_arc        = true
end