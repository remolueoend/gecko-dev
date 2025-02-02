/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_glean_GleanCounter_h
#define mozilla_glean_GleanCounter_h

#include "mozilla/Maybe.h"
#include "nsIGleanMetrics.h"
#include "mozilla/glean/fog_ffi_generated.h"

namespace mozilla::glean {

namespace impl {

class CounterMetric {
 public:
  constexpr explicit CounterMetric(uint32_t aId) : mId(aId) {}

  /*
   * Increases the counter by `amount`.
   *
   * @param aAmount The amount to increase by. Should be positive.
   */
  void Add(int32_t aAmount = 1) const { fog_counter_add(mId, aAmount); }

  /**
   * **Test-only API**
   *
   * Gets the currently stored value as an integer.
   *
   * This function will attempt to await the last parent-process task (if any)
   * writing to the the metric's storage engine before returning a value.
   * This function will not wait for data from child processes.
   *
   * This doesn't clear the stored value.
   * Parent process only. Panics in child processes.
   *
   * @return value of the stored metric, or Nothing() if there is no value.
   */
  Maybe<int32_t> TestGetValue(const nsACString& aStorageName) const {
    if (!fog_counter_test_has_value(mId, &aStorageName)) {
      return Nothing();
    }
    return Some(fog_counter_test_get_value(mId, &aStorageName));
  }

 private:
  const uint32_t mId;
};
}  // namespace impl

class GleanCounter final : public nsIGleanCounter {
 public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIGLEANCOUNTER

  explicit GleanCounter(uint32_t id) : mCounter(id){};

 private:
  virtual ~GleanCounter() = default;

  const impl::CounterMetric mCounter;
};

}  // namespace mozilla::glean

#endif /* mozilla_glean_GleanCounter_h */
