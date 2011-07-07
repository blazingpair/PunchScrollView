//
//  PunchScrollView.h
//  
//
//  Created by tapwork. on 20.10.10. 
//
//  Copyright 2010 tapwork. mobile design & development. All rights reserved.
//  tapwork.de
//

#import <UIKit/UIKit.h>


@protocol PunchScrollViewDataSource;
@protocol PunchScrollViewDelegate;

typedef enum {
    PunchScrollViewDirectionHorizontal = 0,
    PunchScrollViewDirectionVertical = 1,
} PunchScrollViewDirection;

@interface PunchScrollView : UIScrollView <UIScrollViewDelegate> {
	
	id <PunchScrollViewDataSource> punchDataSource_;
	id <PunchScrollViewDelegate> punchDelegate_;
	
	NSMutableSet		*recycledPages_;
    NSMutableSet		*visiblePages_;
	NSInteger			currentPage_;
	NSMutableArray		*indexPaths_;
	CGFloat				oldWidth_;
    CGFloat             pagePadding_;
    CGRect              originalFrame_;
    
    PunchScrollViewDirection direction_;
}



@property (nonatomic, assign) id <PunchScrollViewDataSource> punchDataSource;                  // Set the DataSource for the Scroll Suite
@property (nonatomic, assign) id <PunchScrollViewDelegate> punchDelegate;                      // set the Delegate for the Scroll Suite
@property (nonatomic, assign) CGFloat             pagePadding;                                 // Set the padding between pages  . Default is 10pt
@property (nonatomic, assign) PunchScrollViewDirection direction;                              // Set a Vertical or Horizontal Direction of the scrolling

@property (nonatomic, retain, getter=getCurrentPage) UIView *currentPage;                      //  Get the current visible Page
@property (nonatomic, retain, getter=getFirstPage) UIView *firstPage;                          //  Get the first Page
@property (nonatomic, retain, getter=getLastPage) UIView *lastPage;                            //  Get the last Page
@property (nonatomic, retain, getter=getCurrentIndexPath) NSIndexPath *currentIndexPath;       //  Get the current visible indexPath
@property (nonatomic, retain, getter=getLastIndexPath) NSIndexPath *lastIndexPath;             //  Get the last indexPath of the Scroll Suite




/*
 * Init Method for PunchScrollView
 *
 */
- (id)init; 
- (id)initWithFrame:(CGRect)aFrame;

/*
 * This Method returns a UIView which is in the Queue
 */
- (UIView *)dequeueRecycledPage;


/*
 * This Method reloads the data in the scrollView
 */
- (void)reloadData;


/*
 * This Method returns an UIView for a given indexPath
 *
 */
- (UIView*)pageForIndexPath:(NSIndexPath*)indexPath;

/*
 * Some Scrolling to page methods
 *
 */
- (void)scrollToIndexPath:(NSIndexPath*)indexPath animated:(BOOL)animated;
- (void)scrollToNextPage:(BOOL)animated;
- (void)scrollToPreviousPage:(BOOL)animated;

/*
 * Change the frame of the view
 *
 */
- (void)adjustFrame:(CGRect)aFrame;

@end



/* 
 *  PunchScrollView Delegate Methods
 *
 */

@protocol PunchScrollViewDelegate <NSObject>

@optional

- (void)punchScrollView:(PunchScrollView*)scrollView pageChanged:(NSIndexPath*)indexPath;

@end


/*
 * PunchScrollView DataSource Methods
 *
 */

@protocol PunchScrollViewDataSource <NSObject>

@required

- (NSInteger)punchscrollView:(PunchScrollView *)scrollView numberOfRowsInSection:(NSInteger)section;

- (UIView*)punchScrollView:(PunchScrollView*)scrollView viewForPageAtIndexPath:(NSIndexPath *)indexPath;


@optional

- (NSInteger)numberOfSectionsInPunchScrollView:(PunchScrollView *)scrollView; // Default is 1 if not implemented

@end