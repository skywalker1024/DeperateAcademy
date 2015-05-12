//
//  SaveUtils.cpp
//  BraveFrontier

//  Created by WillArk on 5/6/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#import "AlertView.h"
#include "UserInfo.h"

@implementation AlertView

- (void)init
{
    //[super viewDidLoad];
    // Do any additional setup after loading the view from its nib
    //初始化AlertView
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String: ""] message:[NSString stringWithUTF8String: "主公,请给评价，在评价中留下您的大名，不日上天会赐予您500钻石"]
        delegate:self
        cancelButtonTitle:@"残忍拒绝"
        otherButtonTitles:@"寡人就去",nil];

    
    //这个属性继承自UIView，当一个视图中有多个AlertView时，可以用这个属性来区分
    alert.tag = 1;
    //显示AlertView
    [alert show];
    [alert release];
    
}

#pragma marks -- UIAlertViewDelegate --
//根据被点击按钮的索引处理点击事件
-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSLog(@"buttonIndex=%d",buttonIndex);
    if (alertView.tag == 1 && buttonIndex == 1) {
        NSString * str = [NSString stringWithUTF8String:"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=921871787"];
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
    }
}

/*
//AlertView已经消失时执行的事件
-(void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    NSLog(@"didDismissWithButtonIndex");
}

//ALertView即将消失时的事件
-(void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex
{
    NSLog(@"willDismissWithButtonIndex");
}

//AlertView的取消按钮的事件
-(void)alertViewCancel:(UIAlertView *)alertView
{
    NSLog(@"alertViewCancel");
}

//AlertView已经显示时的事件
-(void)didPresentAlertView:(UIAlertView *)alertView
{
    NSLog(@"didPresentAlertView");
}

//AlertView即将显示时
-(void)willPresentAlertView:(UIAlertView *)alertView
{
    NSLog(@"willPresentAlertView");
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}
*/
@end