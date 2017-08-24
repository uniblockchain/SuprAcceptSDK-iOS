Pod::Spec.new do |s|
  s.name             = "SUPRAcceptSDK"
  s.version          = "2.0.0"
  s.summary          = "Wirecard Payment Platform SDK - credit card payments, Chip and PIN, Magstripe, Alipay"
  s.description      = <<-DESC
                       The library extends the Point of Sale to modern mobile environment. 
                       Major Credit and Debit Card payment processing (Master, Visa, American Express, RuPay) and alternative Payment method support (Alipay)
                       
                       Fully integrated with licensed Wirecard Payment infrastructure.
                       
                       Offering additional business support such as:
                       * Sale Statistics
                       * Cash Management
                       * SAP byDesign integration
                       * Inventory Management
                       
                       Supporting wide range of hardware for accepting a Payment.

                       Terminals:
                       * Spire PosMate, SPm2, SPm20
                       * Miura M010
                       * BBPOS Wisepad 2 family

                       Printers: 
                       * Datecs DPP-250
                       * StarMicronics TSP650
                       * AirPrint
                       
                       Cash Drawers:
                       * StarMicronics mPOP, SMD2
                       
                       Barcode scanners:
                       * SocketMobile Series 7
						
                       DESC
  s.homepage         = "https://github.com/WirecardMobileServices/SuprAcceptSDK-iOS"
  s.license          = 'MIT'
  s.authors           = { "Radoslav Danko" => "radoslav.danko@wirecard.com","Francisco Fortes" => "francisco.fortes@wirecard.com","Marek Timko" => "marek.timko@wirecard.com"}
  s.source           = { :git => "https://github.com/WirecardMobileServices/SuprAcceptSDK-iOS.git", :tag => s.version.to_s }
  s.platform     = :ios, '9.0'
  s.requires_arc = true
  s.libraries = 'stdc++.6', 'z.1', 'xml2'
  s.frameworks    = 'Foundation', 'SystemConfiguration', 'MediaPlayer', 'AVFoundation', 'AudioToolbox', 'CoreAudio', 'ExternalAccessory'
  s.default_subspec = 'Core'
  
  s.subspec 'Core' do |ss|
    ss.vendored_frameworks  = ['Pod/Classes/frameworks/Accept.framework']
    ss.resource = ['Pod/Assets/*.*', 'Pod/Classes/frameworks/acceptResources.bundle']
    ss.dependency 'ZipArchive', '~> 1.4'
    ss.dependency 'Overcoat', '~> 4.0.0-beta.1'
    ss.dependency 'Lockbox' 
	ss.dependency 'libextobjc/EXTScope', '~> 0.4'    
	ss.dependency 'BerTlv'
	ss.dependency 'CocoaLumberjack', '~> 3.0'    
  end  
   

  s.subspec 'BBPOS' do |ss|
    ss.vendored_frameworks  = 'Pod/Classes/frameworks/BBPOS_SDK.framework'
    ss.dependency     'SUPRAcceptSDK/Core'    
  end  

  s.subspec 'Spire' do |ss|
    ss.vendored_frameworks  = 'Pod/Classes/frameworks/Spire_SDK.framework'
    ss.dependency     'SUPRAcceptSDK/Core'    
  end  

  s.subspec 'Datecs' do |ss|
    ss.vendored_frameworks  = 'Pod/Classes/frameworks/Datecs_SDK.framework'
    ss.dependency     'SUPRAcceptSDK/Core' 
  end  
  
  s.subspec 'Stario' do |ss|
    ss.vendored_frameworks  = 'Pod/Classes/frameworks/Stario_SDK.framework'
    ss.dependency     'SUPRAcceptSDK/Core' 
  end    

  s.subspec 'Socket' do |ss|
    ss.vendored_frameworks  = 'Pod/Classes/frameworks/Socket_SDK.framework'
    ss.dependency     'SUPRAcceptSDK/Core' 
  end   
  
  s.subspec 'All' do |ss|
    ss.dependency     'SUPRAcceptSDK/Core' 
	ss.dependency     'SUPRAcceptSDK/BBPOS' 
	ss.dependency     'SUPRAcceptSDK/Spire' 	
	ss.dependency     'SUPRAcceptSDK/Datecs' 	
	ss.dependency     'SUPRAcceptSDK/Stario' 		
	ss.dependency     'SUPRAcceptSDK/Socket' 		
  end   
  
end