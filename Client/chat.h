
#ifndef CHAT_H
#define CHAT_H


void sendMessage(const char *sender, const char *receiver, const char *message);
void setBio(const char *username, const char *bio);
void displayBio(const char *username);

#endif // CHAT_H
