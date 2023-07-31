#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	 struct HashType *prev;
	 struct RecordType *data;
	 struct HashType *next; 
};

// Compute the hash function
int hash(int x)
{
	int val = (x % 100);

	return val;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("Index %d -> ", i);
        struct HashType *cur;
		*cur =  pHashArray[i];
        while (cur != NULL)
        {
            printf("%d %c %d -> ", cur->data->id, cur->data->name, cur->data->order);
            cur = cur->prev;
        }
        printf("\n");
	}
}
void insert(struct HashType array[], struct RecordType record)
{
    int index = hash(record.id);

    struct HashType *newNode = malloc(sizeof(struct HashType));
    *newNode->data = record;
    newNode->next = NULL;

    if (array[index].prev == NULL && array[index].next == NULL)
    {
        array[index] = *newNode;
    }
    else
    {
        struct HashType *cur;
		 *cur = array[index];
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = newNode;

			
    }
}
int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType *hashedRecords = malloc(sizeof(struct HashType)* recordSz);

	
	
	for (int i = 0; i < recordSz; i++)
		insert(hashedRecords, *pRecords);
	
	
}