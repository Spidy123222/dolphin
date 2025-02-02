// Copyright 2020 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ConfigWiiViewController : UITableViewController

@property (weak, nonatomic) IBOutlet DOLSwitch* m_pal60_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_screen_saver_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_sd_card_switch;
@property (weak, nonatomic) IBOutlet DOLSlider* m_ir_slider;
@property (weak, nonatomic) IBOutlet DOLSlider* m_volume_slider;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_rumble_switch;

@end

NS_ASSUME_NONNULL_END
