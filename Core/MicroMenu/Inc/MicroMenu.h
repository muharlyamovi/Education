/**
              MICRO-MENU V2

          (C) Dean Camera, 2012
        www.fourwalledcubicle.com
     dean [at] fourwalledcubicle.com

        Royalty-free for all uses.
	                                  */
#ifndef _MICRO_MENU_H_
#define _MICRO_MENU_H_

#include <stddef.h>
#include <stdint.h>
#include "ssd1306.h"

#define MENU_ITEM_READ_POINTER(Addr) (Addr)
#define MENU_ITEM(Name, Next, Previous, Parent, Child, SelectFunc, EnterFunc, Text) \
	extern Menu_Item_t  Next;     	\
	extern Menu_Item_t  Previous;   \
	extern Menu_Item_t  Parent;     \
	extern Menu_Item_t  Child;  	\
	Menu_Item_t  Name = {&Next, &Previous, &Parent, &Child, SelectFunc, EnterFunc, Text}

struct flag_menu {
	 uint8_t flag_m1;
	 uint8_t flag_m2;
	 uint8_t flag_m3;
	 uint8_t flag_m4;
	 uint8_t flag_m5;
};

extern struct flag_menu flag_m;

	//#include "MenuConfig.h"

/** Введите определение для пункта меню. Пункты меню должны быть инициализированы через хелпер
* макрос \ref MENU_ITEM(), не созданный из этого типа непосредственно в пользовательском коде.
*/
	typedef const struct Menu_Item {
		const struct Menu_Item *Next; /**< Pointer to the next menu item of this menu item */
		const struct Menu_Item *Previous; /**< Pointer to the previous menu item of this menu item */
		const struct Menu_Item *Parent; /**< Pointer to the parent menu item of this menu item */
		const struct Menu_Item *Child; /**< Pointer to the child menu item of this menu item */
		void (*SelectCallback)(void); /**< Pointer to the optional menu-specific select callback of this menu item */
		void (*EnterCallback)(void); /**< Pointer to the optional menu-specific enter callback of this menu item */
		const char Text[]; /**< Menu item text to pass to the menu display callback function */
	} Menu_Item_t;

	/** Создает новую запись пункта меню с указанными ссылками и обратными вызовами.
	*
	* \param[in] Name Имя пункта меню должно быть уникальным.
	* \param[in] Next Имя следующего связанного пункта меню или \ref NULL_MENU, если нет ссылки на меню.
	* \param[in] Previous Имя предыдущего связанного пункта меню или \ref NULL_MENU, если ссылка на меню отсутствует.
	* \param[in] Parent Имя связанного с родительским пунктом меню или \ref NULL_MENU, если ссылка на меню отсутствует.
	* \param[in] Child Имя связанного с дочерним пунктом меню или \ref NULL_MENU, если ссылка на меню отсутствует.
	* \param[in] SelectFunc Обратный вызов функции для выполнения при выборе пункта меню или \c NULL, если нет обратного вызова.
	* \param[in] EnterFunc Обратный вызов функции, выполняемый при входе в пункт меню, или \c NULL, если нет обратного вызова.
	*/

	/** Относительная запись меню навигации для \reef Menu Navigate(), чтобы перейти к родительскому меню. */
	#define MENU_PARENT         Menu_GetCurrentMenu()->Parent

	/** Относительная запись меню навигации для \reef Menu Navigate(), чтобы перейти к дочернему меню. */
	#define MENU_CHILD          Menu_GetCurrentMenu()->Child

	/** Относительная навигационная запись меню для \ref Menu_Navigate() для перехода к следующему связанному элементу меню. */
	#define MENU_NEXT           Menu_GetCurrentMenu()->Next

	/** Относительная навигационная запись меню для \ref Menu_Navigate(), чтобы перейти к предыдущему связанному элементу меню. */
	#define MENU_PREVIOUS       Menu_GetCurrentMenu()->Previous

	/** Пустая запись меню, используемая в определениях \ref MENU_ITEM(), где не должно быть ссылки на меню. */
	extern Menu_Item_t  NULL_MENU;

	/** Retrieves the currently selected meny item.
	 *
	 *  \return Pointer to the currently selected meny item.
	 */
	Menu_Item_t* Menu_GetCurrentMenu(void);

	/** Переход к абсолютному или относительному элементу меню.
	*
	* \param[in] NewMenu Указатель на абсолютный пункт меню для выбора или один из \ref MENU_PARENT,
	* \ref MENU_CHILD, \ref MENU_NEXT или \ref MENU_PREVIOUS для относительной навигации.
	*/
	void Menu_Navigate(Menu_Item_t* const NewMenu);

	/** Настраивает функцию обратного вызова записи текста меню, запускаемую для всех пунктов меню. В этом обратном вызове
	* функция, которую пользователь должен реализовать в коде для отображения текущего текста меню, хранящегося в \ref MENU_ITEM_STORAGE
	* объем памяти.
	*
	* \ref WriteFunc Указатель на функцию обратного вызова, которая будет выполняться для каждого выбранного пункта меню.
	*/
	void Menu_SetGenericWriteCallback(void (*WriteFunc)(const char* Text));

	/** Вход в текущий выбранный пункт меню, запуск его настроенной функции обратного вызова (если есть). */
	void Menu_EnterCurrentItem(void);
	void Menu_General(void);
	void Level1Item1_Enter(void);
	void Level1Item1_Select(void);
	//static void Generic_Write(const char* Text);

#endif
