#include "Murder.h"

void Murder::action() {
    Loc enemy;
    for(int i = 0; i < ai->units.size(); i++){
        if(unit.touched) break;

        Unit& currUnit = units[i];
        if(enemyWithinRange(currUnit, enemy) {
            currUnit.attack(enemy.x(), enemy.y());
            currUnit.touched = true;
        }
        else{
            Loc end;
            std::vector<Loc> res = bfs(Loc(currUnit.x(), currUnit.y()), end, true, currUnit.maxMovement());
            currUnit.move(res[0].x(), res[0].y());
            for(int i = 0; i < currUnit.maxMovement() - 1; i++) {
                if(enemyWithinRange(currUnit, enemy)){
                    currUnit.attack(enemy.x(), emeny.y());
                    currUnit.touched = true;
                    break;
                }
                //move
            }
        }
    }
}


