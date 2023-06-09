/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * *    * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __POWER_HELPER_H__
#define __POWER_HELPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <hardware/power.h>

// These values are used as indices in getSubsystemLowPowerStats(), as source IDs
// in stats_section instances, and (in the case of the _COUNT values) to dimension
// containers.  The values used as indices need to be contiguous, but others do
// not (which is why SYSTEM_STATES is all the way at the end; it is not used as
// an index, but only as a source ID).
enum stats_source {
    // Master stats
    MASTER_APSS = 0,
    MASTER_MPSS,
    MASTER_ADSP,
    MASTER_SLPI,
    // The following 3 masters are supported by the RPMh stats driver, but not
    // in use on our devices.
    // MASTER_CDSP,
    // MASTER_GPU,
    // MASTER_DISPLAY,
    MASTER_COUNT, // Total master sources

    // Don't add any lines after this line
    STATS_SOURCE_COUNT, // Total sources of any kind excluding system states
    SUBSYSTEM_COUNT = STATS_SOURCE_COUNT - MASTER_COUNT,

    SYSTEM_STATES
};

enum master_sleep_states {
    MASTER_SLEEP = 0,

    //Don't add any lines after this line
    MASTER_SLEEP_STATE_COUNT
};

enum master_stats {
    SLEEP_CUMULATIVE_DURATION_MS = 0,
    SLEEP_ENTER_COUNT,
    SLEEP_LAST_ENTER_TSTAMP_MS,

    //Don't add any lines after this line
    MASTER_STATS_COUNT
};

enum system_sleep_states {
    SYSTEM_STATE_AOSD = 0,
    SYSTEM_STATE_CXSD,

    //Don't add any lines after this line
    SYSTEM_SLEEP_STATE_COUNT
};

enum system_state_stats {
    TOTAL_COUNT = 0,
    ACCUMULATED_TIME_MS,

    //Don't add any lines after this line
    SYSTEM_STATE_STATS_COUNT
};

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof((x))/sizeof((x)[0]))
#endif

struct stats_section {
    enum stats_source source;
    const char *label;
    const char **stats_labels;
    size_t num_stats;
};

int extract_master_stats(uint64_t *list, size_t list_length);
int extract_system_stats(uint64_t *list, size_t list_length);
void set_feature(feature_t feature, int state);

#ifdef __cplusplus
}
#endif

#endif //__POWER_HELPER_H__
