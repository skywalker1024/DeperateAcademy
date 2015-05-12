//
//  SaveUtils.h
//  BraveFrontier

//  Created by WillArk on 5/6/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_GumiChinaMessageBox_h
#define BraveFrontier_GumiChinaMessageBox_h

#import <UIKit/UIKit.h>
@interface AlertView : UIViewController<UIAlertViewDelegate>

- (void)init;
-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
-(void)viewDidUnload;
@end

#endif
