/*
 * Copyright (c) 2022, Alibaba Group Holding Limited;
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include "async_simple/coro/Lazy.h"

#include <string>
#include <vector>

using namespace async_simple::coro;
namespace pgn2sqlite {
  using Texts = std::vector<std::string>;

  Lazy<Texts> ReadFile(const std::string& filename);

  Lazy<int> CountLineChar(const std::string& line, char c);

  Lazy<int> CountTextChar(const Texts& Content, char c);

  Lazy<int> CountFileCharNum(const std::string& filename, char c);
} // namespace pgn2sqlite
