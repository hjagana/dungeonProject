#include "KeyboardListener.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>

int count = 1;
bool hallucinate = false;
bool blessCurse = false;

KeyboardListener::KeyboardListener(ObjectDisplayGrid* _grid, Player *_player, Dungeon *_dungeon) : grid(_grid), player(_player), dungeon(_dungeon) {}

void KeyboardListener::run() {
	grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
	// grid->writeTopLine(1, "HPMovesValue: " + std::to_string(player->getHpMoves())); // just used to check if HPmoves was read in correctly from the XML file
	grid->writeLine(0, "Press 'x' to exit");
	//these should be displayed once i is hit
	// grid->writeLine(5, "Pack: ");
	// grid->writeLine(7, "Info: ");
	running = true;
	char input;
	do {
		// input = std::tolower(getchar());
		input = getchar();
		int itemNum = 0;
		int armorNum = 0;
		int scrollNum = 0;
		int swordNum = 0;
		char nextChar = '\0';

		dungeon->setItemCount(count);	

		if (player->getHp() <= 0) {
			player->endGameBoolCheck();
		}
		
		if (player->endGameBool) {
			// running = false;
			switch(input) {
			case 'x':
				running = false;
				grid->writeLine(2, "Exiting...");
				break;	
			case 'i':
				dungeon->displayItemsInPack();
				break;
			case '?':
				grid->writeLine(1, " ");
				grid->writeLine(2, "Info: h,l,k,j,i,?,H,c,d,p,R,T,w,E,0-9. H <cmd> for more info");
				grid->writeLine(3, " ");
				grid->writeLine(4, " ");
				break;
			case 'H':
				nextChar = std::tolower(getchar());
				switch(nextChar){
					case 'h':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move left 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'l':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move right 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'k':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move up 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'j':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move down 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'i':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: inventory, show pack contents");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'c':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: take off/change armor");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'd':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: drop <item number> item from pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'p':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: pick up item under player and put into the pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'r':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: read the scroll which is item number <item in pack number> in pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 't':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: take out weapon from pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'w':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: take out the armor which is item number <item number in pack> in the pack and put it on");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
				}
				break;	
			} 
			grid->update();
		} else {
			switch (input) {
			case 'x':
				running = false;
				grid->writeLine(2, "Exiting...");
				break;
			case 'e':
				//change this to end the game
				grid->writeLine(2, "You found the easter egg, congrats");
				break;
			case 'h':
				if(dungeon->checkMove(player->getXPos() - 1, player->getYPos())){
					if(hallucinate){
						player->updateHallucinateCounter();
						dungeon->hallucinate();
						grid->writeLine(3, "Hallucination will continue for " + std::to_string(player->getHallucinateMaxCount() - player->hallucinateCounter) + " more steps");
						grid->update();
					}
					if(player->hallucinateCounter == player->getHallucinateMaxCount()){
						player->hallucinateCounter = 0;
						hallucinate = false;
						grid->writeLine(3, " ");
						dungeon->drawNormal();
					}
					player->movePlayerLeft();
					player->updateHPmovesCounter();
					if (player->hpMovesCounter == player->getHpMoves() && (player->getHp() < 99)) {
						player->hpMovesCounter = 0;
						player->setHp(player->getHp() + 1);
					} 
					if (player->hpMovesCounter >= player->getHpMoves()) {
						player->hpMovesCounter = 0;
					}
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: LEFT");
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else if (dungeon->checkCollision(player->getXPos() - 1, player->getYPos())){
					int playerHealth = player->getHp();
					if(playerHealth <= 0){
						grid->writeLine(1, " ");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
					}
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else{
					grid->writeLine(1, "");
					grid->writeLine(2, "Info: can not move left");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'l':
				if(dungeon->checkMove(player->getXPos() + 1, player->getYPos())){
					if(hallucinate){
						player->updateHallucinateCounter();
						dungeon->hallucinate();
						grid->writeLine(3, "Hallucination will continue for " + std::to_string(player->getHallucinateMaxCount() - player->hallucinateCounter) + " more steps");
					}
					if(player->hallucinateCounter == player->getHallucinateMaxCount()){
						player->hallucinateCounter = 0;
						hallucinate = false;
						grid->writeLine(3, " ");
						dungeon->drawNormal();
					}
					player->movePlayerRight();
					player->updateHPmovesCounter();
					if (player->hpMovesCounter == player->getHpMoves() && (player->getHp() < 99)) {
						player->hpMovesCounter = 0;
						player->setHp(player->getHp() + 1);
					}
					if (player->hpMovesCounter >= player->getHpMoves()) {
						player->hpMovesCounter = 0;
					}
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: RIGHT");
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else if (dungeon->checkCollision(player->getXPos() + 1, player->getYPos())){
					int playerHealth = player->getHp();
					if(playerHealth <= 0){
						grid->writeLine(1, " ");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
					}
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: can not move right");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'k':
				if(dungeon->checkMove(player->getXPos(), player->getYPos() - 1)){
					if(hallucinate){
						player->updateHallucinateCounter();
						dungeon->hallucinate();
						grid->writeLine(3, "Hallucination will continue for " + std::to_string(player->getHallucinateMaxCount() - player->hallucinateCounter) + " more steps");
					}
					if(player->hallucinateCounter == player->getHallucinateMaxCount()){
						player->hallucinateCounter = 0;
						hallucinate = false;
						grid->writeLine(3, " ");
						dungeon->drawNormal();
					}
					player->movePlayerUp();
					player->updateHPmovesCounter();
					if (player->hpMovesCounter == player->getHpMoves() && (player->getHp() < 99)) {
						player->hpMovesCounter = 0;
						player->setHp(player->getHp() + 1);
					}
					if (player->hpMovesCounter >= player->getHpMoves()) {
						player->hpMovesCounter = 0;
					}
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: UP");
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else if (dungeon->checkCollision(player->getXPos(), player->getYPos() - 1)){
					int playerHealth = player->getHp();
					if(playerHealth <= 0){
						grid->writeLine(1, " ");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
					}
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: can not move up");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'j':
				if(dungeon->checkMove(player->getXPos(), player->getYPos() + 1)){
					if(hallucinate){
						player->updateHallucinateCounter();
						dungeon->hallucinate();
						grid->writeLine(3, "Hallucination will continue for " + std::to_string(player->getHallucinateMaxCount() - player->hallucinateCounter) + " more steps");
					}
					if(player->hallucinateCounter == player->getHallucinateMaxCount()){
						player->hallucinateCounter = 0;
						hallucinate = false;
						grid->writeLine(3, " ");
						dungeon->drawNormal();
					}
					player->movePlayerDown();
					player->updateHPmovesCounter();
					if (player->hpMovesCounter == player->getHpMoves() && (player->getHp() < 99)) {
						player->hpMovesCounter = 0;
						player->setHp(player->getHp() + 1);
					}
					if (player->hpMovesCounter >= player->getHpMoves()) {
						player->hpMovesCounter = 0;
					}
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: DOWN");
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else if (dungeon->checkCollision(player->getXPos(), player->getYPos() + 1)){
					int playerHealth = player->getHp();
					if(playerHealth <= 0){
						grid->writeLine(1, " ");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
					}
					grid->writeTopLine(0, "HP: " + std::to_string(player->getHp()) + "     Score: " + std::to_string(player->getScoreVal()));
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: can not move down");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'i':
				dungeon->displayItemsInPack();
				break;
			case 'c':
				if(dungeon->checkArmor()){
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: take off / change armor");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: no armor is worn");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'd':
				itemNum = std::tolower(getchar());
				if(itemNum - 48 <= 0){
					itemNum = itemNum - 48;
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: can not drop item "  + std::to_string(itemNum) + " from the pack");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
					break;
				}
				if(dungeon->dropItemFromPack(itemNum, count)){
					itemNum = itemNum - 48;
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: drop item "  + std::to_string(itemNum) + " from the pack");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
					count++;
				}
				else{
					itemNum = itemNum - 48;
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: can not drop item "  + std::to_string(itemNum) + " from the pack");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'p':
				if (dungeon->addItemToPack(player->getXPos(), player->getYPos())){
					grid->writeLine(1, " ");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: no item to pick up");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'r':
				scrollNum = std::tolower(getchar());
				if(dungeon->checkScrollInPack(scrollNum)){
					int num = dungeon->performAction(scrollNum, hallucinate, blessCurse);
					if (num == 2){
						hallucinate = true;
					}
					if (num == 3){
						blessCurse = true;
					}
					if(blessCurse){
						dungeon->blessCurse(scrollNum);
						player->removeItemFromPack(scrollNum -  49);
					}
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: read the scroll which is item number " + std::to_string(scrollNum - 48) + " in pack");
					// grid->writeLine(3, " ");
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: no scroll to read with item number " + std::to_string(scrollNum - 48) + " in pack");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
			
				break;
			case 'T':
				swordNum = std::tolower(getchar());
				if(dungeon->checkSwordInPack(swordNum)){
					dungeon->swapSword(swordNum);
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: take the sword identified by " + std::to_string(swordNum - 48) + " from the pack and wield it" );
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: the item identified by " + std::to_string(swordNum - 48) + " number is not in the pack or is not a sword" );
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case 'w':
				armorNum = std::tolower(getchar());
				if (dungeon->checkArmorInPack(armorNum)){
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: take out armor with " + std::to_string(armorNum - 48) + " number from pack and wear it");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				else{
					grid->writeLine(1, " ");
					grid->writeLine(2, "Info: item identified with " + std::to_string(armorNum - 48) + " item number is not an armor ");
					grid->writeLine(3, " ");
					grid->writeLine(4, " ");
				}
				break;
			case '?':
				grid->writeLine(1, " ");
				grid->writeLine(2, "Info: h,l,k,j,i,?,H,c,d,p,R,T,w,E,0-9. H <cmd> for more info");
				grid->writeLine(3, " ");
				grid->writeLine(4, " ");
				break;
			case 'H':
				nextChar = std::tolower(getchar());
				switch(nextChar){
					case 'h':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move left 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'l':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move right 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'k':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move up 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'j':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: move down 1 space");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'i':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: inventory, show pack contents");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'c':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: take off/change armor");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'd':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: drop <item number> item from pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'p':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: pick up item under player and put into the pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'r':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: read the scroll which is item number <item in pack number> in pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 't':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: take out weapon from pack");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
					case 'w':
						grid->writeLine(1, " ");
						grid->writeLine(2, "Info: take out the armor which is item number <item number in pack> in the pack and put it on");
						grid->writeLine(3, " ");
						grid->writeLine(4, " ");
						break;
				}
				break;
			case 'E':
				nextChar = std::tolower(getchar());
				if (nextChar == 'y'){
					//print message on why you died
					player->endGameBoolCheck();
					break;
				}
			default:
				std::string message = "Unknown key '";
				message += input;
				grid->writeLine(1, " ");
				grid->writeLine(2, message + "'");
				grid->writeLine(3, " ");
				grid->writeLine(4, " ");
				break;
			}
			grid->update();
		}
		
	} while (running && input != EOF);
}

// int KeyboardListener::getCount(){
// 	return count;
// }

// void KeyboardListener::setEndGameBool(){
// 	endGame = true;
// }