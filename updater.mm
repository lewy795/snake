#include "updater.h"
#import <Foundation/Foundation.h>
#import <Sparkle/Sparkle.h>

void checkGameUpdates() {
    SPUStandardUpdaterController *updaterController = [[SPUStandardUpdaterController alloc] initWithStartingUpdater:YES updaterDelegate:nil userDriverDelegate:nil];
    [updaterController.updater checkForUpdatesInBackground];
}