/*
 * RCHSentence.cpp
 *
 * (C) Copyright 2016 Pavel Bobov.
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

#include <string.h>
#include <stdlib.h>

#include "Sentences.h"
#include "StrUtils.h"

PWMSentence::PWMSentence() :
  Sentence(TALKER_RC, TAG_PWM),
  channel(1), pulse(0) {
}

PWMSentence::~PWMSentence() {
}

char* PWMSentence::get(char str[], size_t buflen) const {
  if (str == NULL || buflen < MAX_SENTENCE_LENGTH)
    return NULL;

  addHead(str);

  strcat(str, ",");

  char* p = strend(str);

  if (channel >= 0) {
    ltoa2(channel, p, 10);
  }

  strcat(str, ",");

  p = strend(str);

  if (pulse >= 0) {
    ltoa2(pulse, p, 10);
  }

  return addChecksum(str);
}

bool  PWMSentence::set(const char str[]) {
  if (!valid(str))
    return false;

  if (!matches(str))
    return false;

  const char *p = str;

  // get time
  p = nextToken(p);

  if (',' != *p)
    channel = atoi(p);
  else
    channel = -1;

  p = nextToken(p);

  if (',' != *p)
    pulse = atof(p);
  else
    pulse = -1;

  return true;
}
