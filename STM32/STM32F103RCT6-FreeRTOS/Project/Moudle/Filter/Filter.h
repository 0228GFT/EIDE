#ifndef _FILTER_H_
#define _FILTER_H_

#define FILTER_SIZE 10

typedef struct
{
	uint16_t buffer[FILTER_SIZE];
	uint8_t index;
	uint32_t sum;
} MovingAverageFilter;

void Filter_Init(MovingAverageFilter *filter);
void Filter_Update(MovingAverageFilter *filter, uint16_t input, uint16_t *output);

#endif // !_FILTER_H_
