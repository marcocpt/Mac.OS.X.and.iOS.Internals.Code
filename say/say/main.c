//
//  main.c
//  say
//
//  Created by marcow on 2020/12/24.
//  Copyright © 2020 marcow. All rights reserved.
//
//  [LISTING 2-3: Demonstrating a very simple (partial) implementation of the say(1) utility](marginnote3app://note/F5E61407-5506-4178-BF33-6ED29A4023AE)

#include <ApplicationServices/ApplicationServices.h>

int main(int argc, const char * argv[]) {
  OSErr rc;
  SpeechChannel channel;
  VoiceSpec vs;
  int voice;
  const char *text = "What do you want me to say?";
  
  if (!argv[1]) {
    voice = 1;
  } else {
    voice = atoi(argv[1]);
  }
  
  if (argc == 3) { text = argv[2];}
  
  // GetIndVoice gets the voice defined by the (positive) index
  rc= GetIndVoice(voice, // SInt16       index,
                  &vs);  // VoiceSpec *  voice)
  
  // NewSpeechChannel basically makes the voice usable
  rc = NewSpeechChannel(&vs,// VoiceSpec * voice, /* can be NULL */
                        &channel);
  
  // And SpeakText... speaks!
  //  rc = SpeakText(channel,      // SpeechChannel   chan,
  //                 text,          // const void *    textBuf,
  //                 strlen(text)); //unsigned long   textBytes)
  CFStringRef cfText = CFStringCreateWithCString(NULL, text, kCFStringEncodingUTF8);
  rc = SpeakCFString(channel, cfText, NULL);
  
  if (rc) {
    fprintf (stderr,"Unable to speak!\n");
    return 1;
  }
  
  // Because speech is asynchronous, wait until we are done.
  // Objective-C has much nicer callbacks for this.
  while (SpeechBusy()) {
    sleep(1);
  }
  return 0;
}
