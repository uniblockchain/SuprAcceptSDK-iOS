//
//  LoginVC.swift
//  eClear
//
//  Created by Danko, Radoslav on 16/12/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import UIKit

class LoginVC: UIViewController, UIPickerViewDelegate, UIPickerViewDataSource {
 
    @IBOutlet weak var picker: UIPickerView!
    @IBOutlet weak var tUsername: UITextField!
    @IBOutlet weak var tPassword: UITextField!
    @IBOutlet weak var btnLogin: UIButton!
    
    let app:AppDelegate = UIApplication.shared.delegate as! AppDelegate
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    @IBAction func onTapLogin(_ sender: Any) {

        if tUsername.text == "" || tPassword.text == ""{
            app.showError("Login", text: "Username and Password needs to be provided")
        }
        else{
            let arrBackend:NSArray = app.backends! as NSArray
            let backend:NSDictionary = arrBackend.object(at: picker.selectedRow(inComponent: 0)) as! NSDictionary
            let selectedBackend = (backend.value(forKey: "url") as! String)
            

            app.loginUser(tUsername.text, password: tPassword.text, backend: selectedBackend ,completion:{ (success) in
                if(success == true){
                    self.dismiss(animated: true, completion: nil)
                }
                } )
        }
    }
    
    // MARK: - Picker -
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return app.backends.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        let arrBackend:NSArray = app.backends! as NSArray
        let backend:NSDictionary = arrBackend.object(at: row) as! NSDictionary
        return (backend.value(forKey: "url") as! String)
    }
    @IBAction func onTapBackground(_ sender: Any) {
        self.tPassword.resignFirstResponder()
        self.tUsername.resignFirstResponder()
    }
    
}
