#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int capacity;
    int tokens;
    time_t last_fill_time;
} TokenBucket;

void initTokenBucket(TokenBucket *bucket, int capacity) {
    bucket->capacity = capacity;
    bucket->tokens = capacity;
    bucket->last_fill_time = time(NULL);
}

void refillTokens(TokenBucket *bucket, int rate) {
    time_t now = time(NULL);
    double time_diff = difftime(now, bucket->last_fill_time);
    int tokens_to_add = time_diff * rate;
    bucket->tokens = (bucket->tokens + tokens_to_add) < bucket->capacity ? bucket->tokens + tokens_to_add : bucket->capacity;
    bucket->last_fill_time = now;
}

int takeToken(TokenBucket *bucket) {
    if (bucket->tokens > 0) {
        bucket->tokens--;
        return 1; // Token available
    }
    return 0; // No token available
}

int main() {
    TokenBucket bucket;
    int capacity = 10;
    initTokenBucket(&bucket, capacity);
    int rate = 1;

    refillTokens(&bucket, rate);

    for (int i = 0; i < 15; i++) {
        if (takeToken(&bucket)) {
            printf("Token %d taken\n", i);
        } else {
            printf("No token available at time %d\n", i);
        }
    }

    return 0;
}