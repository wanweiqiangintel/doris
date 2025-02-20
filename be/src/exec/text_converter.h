// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <stddef.h>

#include "vec/columns/column.h"

namespace doris {

class SlotDescriptor;

// Helper class for dealing with text data, e.g., converting text data to
// numeric types, etc.
class TextConverter {
public:
    TextConverter(char escape_char);

    void write_string_column(const SlotDescriptor* slot_desc,
                             vectorized::MutableColumnPtr* column_ptr, const char* data,
                             size_t len);

    bool write_column(const SlotDescriptor* slot_desc, vectorized::MutableColumnPtr* column_ptr,
                      const char* data, size_t len, bool copy_string, bool need_escape);

    bool write_vec_column(const SlotDescriptor* slot_desc, vectorized::IColumn* nullable_col_ptr,
                          const char* data, size_t len, bool copy_string, bool need_escape);

    /// Write consecutive rows of the same data.
    bool write_vec_column(const SlotDescriptor* slot_desc, vectorized::IColumn* nullable_col_ptr,
                          const char* data, size_t len, bool copy_string, bool need_escape,
                          size_t rows);
    void unescape_string_on_spot(const char* src, size_t* len);

private:
    char _escape_char;
};

} // namespace doris
