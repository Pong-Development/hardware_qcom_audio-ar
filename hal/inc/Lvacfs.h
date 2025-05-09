/*
 * Copyright (C) 2025 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

class StreamInPrimary;

typedef int (*lvacfs_create_instance_t)(void**, uint32_t, uint64_t, uint32_t);
typedef int (*lvacfs_destroy_instance_t)(void*);
typedef int (*lvacfs_process_t)(void*, void*, void*, int32_t, void*);
typedef void (*lvacfs_set_params_file_path_t)(const char*);
typedef void (*lvacfs_set_profile_t)(void*, uint32_t);
typedef void (*lvacfs_update_zoom_info_t)(void*, float);
typedef void (*lvacfs_update_angle_info_t)(void*, float);
typedef void (*lvacfs_set_audio_direction_t)(void*, uint32_t);
typedef void (*lvacfs_set_device_orientation_t)(void*, uint32_t);
typedef void (*lvacfs_get_versions_t)(char*, size_t);

struct lvacfs_wrapper_ops {
    void* lib_handle;
    lvacfs_create_instance_t create_instance;
    lvacfs_destroy_instance_t destroy_instance;
    lvacfs_process_t process;
    lvacfs_update_zoom_info_t update_zoom_info;
    lvacfs_update_angle_info_t update_angle_info;
    lvacfs_set_params_file_path_t set_params_file_path;
    lvacfs_set_profile_t set_profile;
    lvacfs_set_audio_direction_t set_audio_direction;
    lvacfs_set_device_orientation_t set_device_orientation;
    lvacfs_get_versions_t get_versions;
};

class Lvacfs {
  public:
    static Lvacfs& getInstance() {
        static Lvacfs instance;
        return instance;
    }
  
    void init(void);
    void deinit(void);
    void start_input_stream(StreamInPrimary* in);
    void process_input_stream(StreamInPrimary* in, void* buffer, size_t bytes);
    void stop_input_stream(StreamInPrimary* in);
    
    const struct lvacfs_wrapper_ops* getWrapperOps() const { return wrapper_ops_.get(); }
    
  private:
    Lvacfs() : wrapper_ops_(nullptr), params_file_path_(nullptr) {}

    Lvacfs(const Lvacfs&) = delete;
    Lvacfs& operator=(const Lvacfs&) = delete;

    std::unique_ptr<struct lvacfs_wrapper_ops> wrapper_ops_;
    const char* params_file_path_;
};
