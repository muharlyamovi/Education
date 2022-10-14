/**
              MICRO-MENU V2

          (C) Dean Camera, 2012
        www.fourwalledcubicle.com
     dean [at] fourwalledcubicle.com

        Royalty-free for all uses.
	                                  */

#include "MicroMenu.h"

	// MENU_ITEM(Name, Next, Previous, Parent, Child, SelectFunc, EnterFunc, Text)
	MENU_ITEM(Menu_1, Menu_2, Menu_8, NULL_MENU, Menu_1_1 , Level1Item1_Select, Level1Item1_Enter, "Menu_1");
	MENU_ITEM(Menu_2, Menu_3, Menu_1, NULL_MENU, NULL_MENU, NULL              , NULL, "Menu_2");
	MENU_ITEM(Menu_3, Menu_4, Menu_2, NULL_MENU, NULL_MENU, NULL              , NULL, "Menu_3");
	MENU_ITEM(Menu_4, Menu_5, Menu_3, NULL_MENU, NULL_MENU, NULL              , NULL, "Menu_4");
	MENU_ITEM(Menu_5, Menu_6, Menu_4, NULL_MENU, NULL_MENU, NULL              , NULL, "Menu_5");
	MENU_ITEM(Menu_6, Menu_7, Menu_5, NULL_MENU, NULL_MENU, NULL              , NULL, "Menu_6");
	MENU_ITEM(Menu_7, Menu_8, Menu_6, NULL_MENU, NULL_MENU, NULL              , NULL, "Menu_7");
	MENU_ITEM(Menu_8, Menu_1, Menu_7, NULL_MENU, NULL_MENU, NULL              , NULL, "Menu_8");

	MENU_ITEM(Menu_1_1, Menu_1_2, Menu_1_2, Menu_1, NULL_MENU, NULL, NULL, "1.1");
	MENU_ITEM(Menu_1_2, Menu_1_1, Menu_1_1, Menu_1, NULL_MENU, NULL, NULL, "1.2");

//Menu_Item_t menu_array[] = {&Menu_1, &Menu_2, &Menu_3, &Menu_4, &Menu_5, &Menu_6, &Menu_7, &Menu_8};
uint8_t cursorY = 0;
/** Это используется, когда требуется недопустимый дескриптор меню в
  * определение \ref MENU_ITEM(), то есть указать, что
  * меню не имеет связанной родительской, дочерней, следующей или предыдущей записи.
  */
Menu_Item_t NULL_MENU = {0};

/** \внутренний
  * Указатель на общую функцию отображения текста меню
  * обратный вызов, для отображения настроенного текста пункта меню
  * если не задана функция отображения, специфичная для меню
  * в пункте меню выбора.
  */
static void (*MenuWriteFunc)(const char* Text) = NULL;

/** \внутренний
  * Указатель на текущий выбранный пункт меню.
  */
static Menu_Item_t* CurrentMenuItem = &NULL_MENU;

Menu_Item_t* Menu_GetCurrentMenu(void)
{
	return CurrentMenuItem;
}

void Menu_Navigate(Menu_Item_t* const NewMenu)
{
	if ((NewMenu == &NULL_MENU) || (NewMenu == NULL))
		return;

	CurrentMenuItem = NewMenu;

	if (MenuWriteFunc)
		MenuWriteFunc(CurrentMenuItem->Text);

	void (*SelectCallback)(void) = CurrentMenuItem->SelectCallback;

	if (SelectCallback)
		SelectCallback();
}

void Menu_SetGenericWriteCallback(void (*WriteFunc)(const char* Text))
{
	MenuWriteFunc = WriteFunc;
	Menu_Navigate(CurrentMenuItem);
}

void Menu_EnterCurrentItem(void)
{
	if ((CurrentMenuItem == &NULL_MENU) || (CurrentMenuItem == NULL))
		return;

	void (*EnterCallback)(void) = CurrentMenuItem->EnterCallback;

	if (EnterCallback)
		EnterCallback();
}

/** Пример функции обратного вызова ввода для конкретного пункта меню, запускаемой при входе в соответствующий пункт меню. */
void Level1Item1_Enter(void)
{
	//ssd1306_Fill(Black);
	//ssd1306_SetCursor(50, 30);
	//ssd1306_WriteString("ENTER", Font_6x8, White);
	//ssd1306_UpdateScreen();
}

/** Пример функции обратного вызова select для конкретного пункта меню, запускаемой при выборе связанного пункта меню. */
void Level1Item1_Select(void)
{
	//ssd1306_Fill(Black);
	//ssd1306_SetCursor(50, 30);
	//ssd1306_WriteString("SELECT", Font_6x8, White);
	//ssd1306_UpdateScreen();
}
/** Общая функция для записи текста меню.
  *
  * \param[in] Text Текст выбранного меню для записи в области памяти \ref MENU_ITEM_STORAGE
  */
void Generic_Write(const char* Text)
{
	//ssd1306_Fill(Black);
	//ssd1306_SetCursor(30, 30);
	ssd1306_WriteString((unsigned char*)Text, Font_6x8, White);
	//ssd1306_UpdateScreen();
}

void Menu_General(void){

	ssd1306_Fill(Black);
	Menu_SetGenericWriteCallback(Generic_Write);

	ssd1306_SetCursor(30, 0);
	//menu_array[&Menu_1];
	Menu_Navigate(&Menu_1);
	//MenuWriteFunc(Menu_1->Text);
	//MenuWriteFunc(CurrentMenuItem->Text);

	ssd1306_SetCursor(30, 8);
	Menu_Navigate(&Menu_2);

	ssd1306_SetCursor(30, 16);
	Menu_Navigate(&Menu_3);

	ssd1306_SetCursor(30, 24);
	Menu_Navigate(&Menu_4);

	ssd1306_SetCursor(30, 32);
	Menu_Navigate(&Menu_5);

	ssd1306_SetCursor(30, 40);
	Menu_Navigate(&Menu_6);

	ssd1306_SetCursor(30, 48);
	Menu_Navigate(&Menu_7);

	ssd1306_SetCursor(30, 56);
	Menu_Navigate(&Menu_8);

	ssd1306_SetCursor(10, (cursorY*8));
	ssd1306_WriteString("->", Font_6x8, White);

	char str[20];
	itoa(cursorY+1,str,10);
	ssd1306_SetCursor(115, 4);
	ssd1306_WriteString(str, Font_6x8, White);

	ssd1306_UpdateScreen();
}
