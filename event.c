#include <stdio.h>
#include <string.h>

#define MAX_EVENTS 100

typedef struct {
    char eventID[10];
    int hour;
    int minute;
    int priority;
} Event;

Event heap[MAX_EVENTS];
int heapSize = 0;

// Compare two events: return 1 if a has higher priority (i.e. should come before b)
int compare(Event a, Event b) {
    if (a.priority != b.priority)
        return a.priority < b.priority;  // lower number = higher priority
    if (a.hour != b.hour)
        return a.hour < b.hour;  // earlier time first
    return a.minute < b.minute;
}

void swap(Event *a, Event *b) {
    Event temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (compare(heap[index], heap[parent])) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else break;
    }
}

void heapify_down(int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heapSize && compare(heap[left], heap[smallest]))
            smallest = left;
        if (right < heapSize && compare(heap[right], heap[smallest]))
            smallest = right;
        if (smallest != index) {
            swap(&heap[index], &heap[smallest]);
            index = smallest;
        } else break;
    }
}

void insertEvent(char *id, int h, int m, int p) {
    strcpy(heap[heapSize].eventID, id);
    heap[heapSize].hour = h;
    heap[heapSize].minute = m;
    heap[heapSize].priority = p;
    heapify_up(heapSize);
    heapSize++;
}

Event removeEvent() {
    Event top = heap[0];
    heap[0] = heap[--heapSize];
    heapify_down(0);
    return top;
}

int main() {
    insertEvent("E101", 9, 30, 3);
    insertEvent("E102", 8, 45, 1);
    insertEvent("E103", 11, 0, 2);
    insertEvent("E104", 10, 15, 4);
    insertEvent("E105", 14, 0, 2);
    insertEvent("E106", 9, 0, 1);
    insertEvent("E107", 16, 30, 5);
    insertEvent("E108", 12, 45, 3);
    insertEvent("E109", 13, 15, 2);
    insertEvent("E110", 15, 0, 4);

    printf("Order of event execution based on priority:\n");
    while (heapSize > 0) {
        Event e = removeEvent();
        printf("%s at %02d:%02d (Priority: %d)\n",
               e.eventID, e.hour, e.minute, e.priority);
    }

    return 0;
}