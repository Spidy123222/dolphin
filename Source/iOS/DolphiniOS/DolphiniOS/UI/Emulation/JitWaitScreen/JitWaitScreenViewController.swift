// Copyright 2021 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

import Foundation

@objc class JitWaitScreenViewController : UIViewController
{
  @objc weak var delegate: JitScreenDelegate?
  var cancellation_token = DOLCancellationToken()
  
  override func viewDidLoad()
  {
    NotificationCenter.default.addObserver(self, selector: #selector(jitAcquired), name: NSNotification.Name.DOLJitAcquired, object: nil)
    NotificationCenter.default.addObserver(self, selector: #selector(altJitFailed), name: NSNotification.Name.DOLJitAltJitFailure, object: nil)
    
    DOLJitManager.shared().attemptToAcquireJitByWaitingForDebugger(using: cancellation_token)
    
    let device_id = Bundle.main.object(forInfoDictionaryKey: "ALTDeviceID") as! String
    if (device_id != "dummy")
    {
      // ALTDeviceID has been set, so we should attempt to acquire by AltJIT instead
      // of just sitting around and waiting for a debugger.
      DOLJitManager.shared().attemptToAcquireJitByAltJIT()
    }
  }
  
  @objc func jitAcquired(notification: Notification)
  {
    DispatchQueue.main.async {
      self.delegate?.DidFinishJitScreen(result: true, sender: self)
    }
  }
  
  @objc func altJitFailed(notification: Notification)
  {
    let error_string: String
    
    if let error = notification.userInfo!["nserror"] as? NSError
    {
      error_string = error.localizedDescription
    }
    else
    {
      error_string = "No error message available."
    }
    
    let alert = UIAlertController.init(title: "Failed to Contact AltJIT", message: error_string, preferredStyle: .alert)
    
    alert.addAction(UIAlertAction.init(title: "Wait for Other Debugger", style: .default, handler: nil))
    
    alert.addAction(UIAlertAction.init(title: "Retry AltJIT", style: .default, handler: { action in
      DOLJitManager.shared().attemptToAcquireJitByAltJIT()
    }))
    
    alert.addAction(UIAlertAction.init(title: "Cancel", style: .cancel, handler: { _ in
      self.cancellation_token.cancel()
      
      self.delegate?.DidFinishJitScreen(result: false, sender: self)
    }))
    
    DispatchQueue.main.async {
      self.present(alert, animated: true, completion: nil)
    }
  }
  
  @IBAction func cancelPressed(_ sender: Any)
  {
    self.cancellation_token.cancel()
    
    self.delegate?.DidFinishJitScreen(result: false, sender: self)
  }
  
}