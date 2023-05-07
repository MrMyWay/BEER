#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _bottle Beer; // Mock type to be used in creating linked data structure

typedef struct _bottle {
	Beer* nextBeer;
	char* beerBrand;
} Beer;

typedef struct {
	Beer* firstBeer;
	int beerCount;
} Wall;

char* brand [9] = {"Bud Ice", "Schlitz", "Olde English 800", "Nattie Bo", "Miller Genuine Draft",
	"Colt 45", "Mickey's", "Lime-A-Rita", "Pabst Blue Ribbon"};

void InitializeWall(Wall *pWall); // Sets the wall up, empty.
Beer* GenerateBeer (void); // Makes a beer bottle and gives it a brand.
void StockBeer(Wall *pWall, Beer *pNewBeer); // Inserts a beer into the wall structure.
void StockWall(Wall *pWall, int total); // Puts the appropriate amount of beer on the wall.
void RecycleBottle(Wall *pWall); // Removes empty beer structures to prevent memory leaks.
void AbuseAlcohol(Wall *pWall); // The "fun" part of the game.

int main(void) {
	srand(time(NULL));
	Wall wall;
	int totalBeers = -1;
	printf("Let's play a horrifying \"game\" that nobody likes!\n");
	printf("Give me a total number of bottles of beer: ");
	scanf("%d", &totalBeers);
	if ((totalBeers < 1) || totalBeers > 100) {
		printf("Silly goose! There can only be between 1 and 100 beers on the wall at the start!\n");
		return 1;
	} else {
		InitializeWall(&wall);
		StockWall(&wall, totalBeers);
		while (wall.beerCount > 0) {
			AbuseAlcohol(&wall);
		}
	}
	return 0;
}

void InitializeWall(Wall *pWall) {
	pWall->beerCount = 0;
	pWall->firstBeer = NULL;
}

Beer* GenerateBeer (void) {
	Beer *pNewBeer;
	pNewBeer = (Beer*)calloc(1, sizeof(Beer));
	pNewBeer->nextBeer = NULL;
	pNewBeer->beerBrand = brand[rand()%9];
	return pNewBeer;
}

void StockBeer(Wall *pWall, Beer *pNewBeer) {
	pNewBeer->nextBeer = pWall->firstBeer;
	pWall->firstBeer = pNewBeer;
	pWall->beerCount++;
}

void StockWall(Wall *pWall, int total) {
	StockBeer(pWall, GenerateBeer());
	while (pWall->beerCount < total) {
		StockBeer(pWall, GenerateBeer());
	}
}

void RecycleBottle(Wall *pWall) {
	Beer *pWasteBeer;
	Beer *pNextBeer;
	pWasteBeer = pWall->firstBeer;
	if (pWall->beerCount == 1) {
		pWall->beerCount = 0;
		pWall->firstBeer = NULL;
	} else {
	pNextBeer = pWasteBeer->nextBeer;
	pWall->firstBeer = pNextBeer;
	pWall->beerCount--;
	free(pWasteBeer);
	}
}

void AbuseAlcohol(Wall *pWall) {
	char* label;
	int currentBottle = pWall->beerCount;
	label = pWall->firstBeer->beerBrand;
	fprintf(stdout, "%d bottle%sof beer on the wall! ", currentBottle, currentBottle != 1 ? "s " : " ");
	fprintf(stdout, "%d bottle%sof beer!\n", currentBottle, currentBottle != 1 ? "s " : " ");
	RecycleBottle(pWall);
	currentBottle = pWall->beerCount;
	fprintf(stdout, "Take one down, pass it around... %d bottle%sof beer on the wall!\n", currentBottle, currentBottle != 1 ? "s " : " ");
	fprintf(stdout, "  (That one was great!  It was a %s.)\n", label);
}
