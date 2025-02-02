/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef _mozilla_dom_BindingIPCUtils_h
#define _mozilla_dom_BindingIPCUtils_h

#include "mozilla/dom/BindingDeclarations.h"
#include "ipc/EnumSerializer.h"

namespace IPC {
template <>
struct ParamTraits<mozilla::dom::CallerType>
    : public ContiguousEnumSerializerInclusive<
          mozilla::dom::CallerType, mozilla::dom::CallerType::System,
          mozilla::dom::CallerType::NonSystem> {};
}  // namespace IPC
#endif  // _mozilla_dom_BindingIPCUtils_h