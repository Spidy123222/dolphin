// Copyright 2020 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface GraphicsEnhancementsViewController : UITableViewController

@property (weak, nonatomic) IBOutlet UILabel* m_efb_scale_label;
//@property (weak, nonatomic) IBOutlet UILabel* m_anti_aliasing_label;
@property (weak, nonatomic) IBOutlet UILabel* m_anisotropic_filtering_label;
@property (weak, nonatomic) IBOutlet UILabel* m_scaled_efb_label;
@property (weak, nonatomic) IBOutlet UILabel* m_texture_filtering_label;
@property (weak, nonatomic) IBOutlet UILabel* m_fog_label;
@property (weak, nonatomic) IBOutlet UILabel* m_copy_filter_label;
@property (weak, nonatomic) IBOutlet UILabel* m_per_pixel_label;
@property (weak, nonatomic) IBOutlet UILabel* m_widescreen_label;
@property (weak, nonatomic) IBOutlet UILabel* m_high_bit_color_label;
@property (weak, nonatomic) IBOutlet UILabel* m_mipmap_label;

@property (weak, nonatomic) IBOutlet DOLSwitch* m_scaled_efb_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_texture_filtering_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_fog_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_copy_filter_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_per_pixel_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_widescreen_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_high_bit_color_switch;
@property (weak, nonatomic) IBOutlet DOLSwitch* m_mipmap_switch;

@end

NS_ASSUME_NONNULL_END
