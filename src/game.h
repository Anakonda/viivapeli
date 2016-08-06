#include "renderer.h"
#include "button.h"

#include <allegro5/allegro.h>

#include <vector>
#include <algorithm>

extern ALLEGRO_EVENT_QUEUE *eventQueue;

class Game
{
	public:
		Game();
		bool mainloop();

		Coordinates tempPoint;
		bool makingLine;
		bool placingCross;

		unsigned char extraPoints;

		std::unordered_set<Coordinates> validPoints;
		std::unordered_set<Coordinates> startPoints;
		std::vector<Line> lines;

		std::vector<Widget*> widgets;
		Button* crossPlaceButton;

		std::vector<Line> possibleMoves;
		bool showPossibleMoves;

		struct Move
		{
			int type;
			union
			{
				Line line;
				Coordinates point;
			};
			Move() { memset( this, 0, sizeof( Move ) ); }
		};

		std::vector<Move> moveHistory;
};
