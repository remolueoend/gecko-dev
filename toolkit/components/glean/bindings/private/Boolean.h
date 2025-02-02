/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_glean_GleanBoolean_h
#define mozilla_glean_GleanBoolean_h

#include "nsIGleanMetrics.h"
#include "mozilla/glean/fog_ffi_generated.h"

namespace mozilla {
namespace glean {

namespace impl {

class BooleanMetric {
 public:
  constexpr explicit BooleanMetric(uint32_t id) : mId(id) {}

  /**
   * Set to the specified boolean value.
   *
   * @param value the value to set.
   */
  void Set(bool value) const { fog_boolean_set(mId, int(value)); }

  /**
   * **Test-only API**
   *
   * Gets the currently stored value as a boolean.
   *
   * This function will attempt to await the last parent-process task (if any)
   * writing to the the metric's storage engine before returning a value.
   * This function will not wait for data from child processes.
   *
   * This doesn't clear the stored value.
   * Parent process only. Panics in child processes.
   *
   * @return value of the stored metric.
   */
  Maybe<bool> TestGetValue(const nsACString& aStorageName) const {
    if (!fog_boolean_test_has_value(mId, &aStorageName)) {
      return Nothing();
    }
    return Some(fog_boolean_test_get_value(mId, &aStorageName));
  }

 private:
  const uint32_t mId;
};
}  // namespace impl

class GleanBoolean final : public nsIGleanBoolean {
 public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIGLEANBOOLEAN

  explicit GleanBoolean(uint32_t id) : mBoolean(id){};

 private:
  virtual ~GleanBoolean() = default;

  const impl::BooleanMetric mBoolean;
};

}  // namespace glean
}  // namespace mozilla

#endif /* mozilla_glean_GleanBoolean.h */
