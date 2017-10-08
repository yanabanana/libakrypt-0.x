/* ----------------------------------------------------------------------------------------------- */
/*   Copyright (c) 2008-2016 by Axel Kenzo, axelkenzo@mail.ru                                      */
/*   All rights reserved.                                                                          */
/*                                                                                                 */
/*  Разрешается повторное распространение и использование как в виде исходного кода, так и         */
/*  в двоичной форме, с изменениями или без, при соблюдении следующих условий:                     */
/*                                                                                                 */
/*   1. При повторном распространении исходного кода должно оставаться указанное выше уведомление  */
/*      об авторском праве, этот список условий и последующий отказ от гарантий.                   */
/*   2. При повторном распространении двоичного кода должна сохраняться указанная выше информация  */
/*      об авторском праве, этот список условий и последующий отказ от гарантий в документации     */
/*      и/или в других материалах, поставляемых при распространении.                               */
/*   3. Ни имя владельца авторских прав, ни имена его соратников не могут быть использованы в      */
/*      качестве рекламы или средства продвижения продуктов, основанных на этом ПО без             */
/*      предварительного письменного разрешения.                                                   */
/*                                                                                                 */
/*  ЭТА ПРОГРАММА ПРЕДОСТАВЛЕНА ВЛАДЕЛЬЦАМИ АВТОРСКИХ ПРАВ И/ИЛИ ДРУГИМИ СТОРОНАМИ "КАК ОНА ЕСТЬ"  */
/*  БЕЗ КАКОГО-ЛИБО ВИДА ГАРАНТИЙ, ВЫРАЖЕННЫХ ЯВНО ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ             */
/*  ОГРАНИЧИВАЯСЬ ИМИ, ПОДРАЗУМЕВАЕМЫЕ ГАРАНТИИ КОММЕРЧЕСКОЙ ЦЕННОСТИ И ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ */
/*  ЦЕЛИ. НИ В КОЕМ СЛУЧАЕ НИ ОДИН ВЛАДЕЛЕЦ АВТОРСКИХ ПРАВ И НИ ОДНО ДРУГОЕ ЛИЦО, КОТОРОЕ МОЖЕТ    */
/*  ИЗМЕНЯТЬ И/ИЛИ ПОВТОРНО РАСПРОСТРАНЯТЬ ПРОГРАММУ, КАК БЫЛО СКАЗАНО ВЫШЕ, НЕ НЕСЁТ              */
/*  ОТВЕТСТВЕННОСТИ, ВКЛЮЧАЯ ЛЮБЫЕ ОБЩИЕ, СЛУЧАЙНЫЕ, СПЕЦИАЛЬНЫЕ ИЛИ ПОСЛЕДОВАВШИЕ УБЫТКИ,         */
/*  ВСЛЕДСТВИЕ ИСПОЛЬЗОВАНИЯ ИЛИ НЕВОЗМОЖНОСТИ ИСПОЛЬЗОВАНИЯ ПРОГРАММЫ (ВКЛЮЧАЯ, НО НЕ             */
/*  ОГРАНИЧИВАЯСЬ ПОТЕРЕЙ ДАННЫХ, ИЛИ ДАННЫМИ, СТАВШИМИ НЕПРАВИЛЬНЫМИ, ИЛИ ПОТЕРЯМИ ПРИНЕСЕННЫМИ   */
/*  ИЗ-ЗА ВАС ИЛИ ТРЕТЬИХ ЛИЦ, ИЛИ ОТКАЗОМ ПРОГРАММЫ РАБОТАТЬ СОВМЕСТНО С ДРУГИМИ ПРОГРАММАМИ),    */
/*  ДАЖЕ ЕСЛИ ТАКОЙ ВЛАДЕЛЕЦ ИЛИ ДРУГОЕ ЛИЦО БЫЛИ ИЗВЕЩЕНЫ О ВОЗМОЖНОСТИ ТАКИХ УБЫТКОВ.            */
/*                                                                                                 */
/*   ak_curves.h                                                                                   */
/* ----------------------------------------------------------------------------------------------- */
#ifndef    __AK_CURVES_H__
#define    __AK_CURVES_H__

/* ----------------------------------------------------------------------------------------------- */
 #include <ak_mpzn.h>

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Структура для символьного описания параметров эллиптической кривой в форме Вейерштрасса */
/*! Структура определяет эллиптическую кривую, заданную в короткой форме Вейерштрасса сравнением
    \f$ y^2 \equiv x^3 + ax + b \pmod{p} \f$, а также образующую точку \f$P=(x_P, y_P)\f$
    на этой кривой с заданным порядком \f$ q \f$.

    Порядок \f$ m \f$ всей группы точек эллиптической кривой может быть определен
    из равенства \f$ m = dq \f$, где величину \f$ d \f$ называют кофактором.

    Параметры \f$ n_0, r, r_2\f$ вводятся для оптимизации вычислений. Определим \f$ r = 2^{256}\f$
    или \f$ r=2^{512}\f$, тогда \f$ n_0 \equiv n \pmod{2^{64}}\f$,
    где \f$ n \equiv -p^{-1} \pmod{r}\f$.
    Величина \f$ r_2 \f$ удовлетворяет сравнению \f$ r_2 \equiv r^2 \pmod{p}\f$.                   */
/* ----------------------------------------------------------------------------------------------- */
 struct wcurve_paramset {
 /*! \brief Количество слов в элементах конечного поля, может принимать значения \ref ak_mpzn256_size или \ref ak_mpzn512_size. */
  size_t size;
 /*! \brief Коэффициент \f$ a \f$ эллиптической кривой. */
  const char *ca;
 /*! \brief Коэффициент \f$ b \f$ эллиптической кривой. */
  const char *cb;
 /*! \brief Модуль \f$ p \f$ эллиптической кривой. */
  const char *cp;
 /*! \brief Порядок \f$ q \f$ подгруппы, порождаемой образующей точкой \f$ P \f$. */
  const char *cq;
 /*! \brief x-координата образующей точки \f$ P = (x_P, y_P) \f$. */
  const char *cpx;
 /*! \brief y-координата образующей точки \f$ P = (x_P, y_P) \f$. */
  const char *cpy;
 /*! \brief Величина \f$ r^2 \pmod{p} \f$, используемая в арифметике Монтгомери. */
  const char *cr2;
 /*! \brief Константа \f$ n_0 \f$, используемая в арифметике Монтгомери по модулю \f$ p \f$. */
  ak_uint64 cn;
 /*! \brief Кофактор порядка подгруппы, т.е. \f$ m = qd \f$, где \f$ m \f$ порядок всей группы. */
  ak_uint64 cd;
};
 typedef struct wcurve_paramset *ak_wcurve_paramset;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Класс, реализующий эллиптическую кривую, заданную в короткой форме Вейерштрасса

   Класс определяет эллиптическую кривую, заданную в короткой форме Вейерштрасса, сравнением
   \f$ y^2 \equiv x^3 + ax + b \pmod{p} \f$, а также образующую точку \f$P=(x_P, y_P)\f$
    на этой кривой с заданным порядком \f$ q \f$.

    Порядок \f$ m \f$ всей группы точек эллиптической кривой может быть определен
    из равенства \f$ m = dq \f$, где величину \f$ d \f$ называют кофактором.

    Параметры \f$ n_0, r, r_2\f$ вводятся для оптимизации вычислений. Определим \f$ r = 2^{256}\f$
    или \f$ r=2^{512}\f$, тогда \f$ n_0 \equiv n \pmod{2^{64}}\f$,
    где \f$ n \equiv -p^{-1} \pmod{r}\f$.
    Величина \f$ r_2 \f$ удовлетворяет сравнению \f$ r_2 \equiv r^2 \pmod{p}\f$.                   */
/* ----------------------------------------------------------------------------------------------- */
 struct wcurve
{
 /*! \brief Количество слов в элементах конечного поля, может быть ak_mpzn256(512)_size */
  size_t size;
 /*! \brief Коэффициент \f$ a \f$ эллиптической кривой */
  ak_uint64 *a;
 /*! \brief Коэффициент \f$ b \f$ эллиптической кривой */
  ak_uint64 *b;
 /*! \brief Модуль \f$ p \f$ эллиптической кривой */
  ak_uint64 *p;
 /*! \brief Порядок \f$ q \f$ подгруппы, порождаемой образующей точкой \f$ P \f$ */
  ak_uint64 *q;
 /*! \brief Удвоенная степень двойки по модулю \f$p\f$, используемая в арифметике Монтгомери */
  ak_uint64 *r2;
 /*! \brief Константа \f$ n \f$, используемая в арифметике Монтгомери */
  ak_uint64 n;
 /*! \brief Кофактор порядка подгруппы, т.е. \f$ m = qd \f$, где \f$ m \f$ порядок всей группы */
  ak_uint64 d;
};
/*! Контекст эллиптической кривой в короткой форме Вейерштрасса */
 typedef struct wcurve *ak_wcurve;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация контекста эллиптической кривой в короткой форме Вейерштрасса. */
 int ak_wcurve_create( ak_wcurve , ak_wcurve_paramset );
/*! \brief Уничтожение данных из контекста эллиптической кривой. */
 int ak_wcurve_destroy( ak_wcurve );
/*! \brief Уничтожение контекста эллиптической кривой. */
 ak_pointer ak_wcurve_delete( ak_pointer );
/*! \brief Вычисление дискриминанта эллиптической кривой, заданной в короткой форме Вейерштрасса. */
 void ak_mpzn_set_wcurve_discriminant( ak_uint64 *, ak_wcurve );
/*! \brief Проверка корректности дискриминанта эллиптической кривой, заданной в форме Вейерштрасса. */
 ak_bool ak_wcurve_discriminant_is_ok( ak_wcurve );
/*! \brief Проверка набора параметров эллиптической кривой, заданной в форме Вейерштрасса. */
 int ak_wcurve_paramset_is_ok( const ak_wcurve_paramset );
/*! \brief Функция тестирует все определяемые библиотекой параметры эллиптических кривых, заданных
                                                                    в короткой форме Вейерштрасса. */
 ak_bool ak_wcurve_test_paramset( void );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Класс, реализующий точку эллиптической кривой.

    Класс реализут точку \f$ P \f$ эллиптической кривой, заданной в короткой форме Вейерштрасса,
    в проективных координатах, т.е. точка представляется в виде вектора \f$ P=(x:y:z) \f$,
    удовлетворяющего сравнению \f$ y^2z \equiv x^3 + axz^2 + bz^3 \pmod{p} \f$.
    В дальнейшем, при проведении вычислений, для координат точки
    используется представление Монтгомери.                                                         */
/* ----------------------------------------------------------------------------------------------- */
 struct wpoint
{
/*! \brief x-координата точки эллиптической кривой */
 ak_uint64 *x;
/*! \brief y-координата точки эллиптической кривой */
 ak_uint64 *y;
/*! \brief z-координата точки эллиптической кривой */
 ak_uint64 *z;
};
/*! \brief Контекст точки эллиптической кривой в короткой форме Вейерштрасса */
 typedef struct wpoint *ak_wpoint;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация контекста точки эллиптической кривой в короткой форме Вейерштрасса. */
 int ak_wpoint_create( ak_wpoint , ak_wcurve_paramset );
/*! \brief Инициализация и присвоение контексту точки значения бесконечно удаленной точки эллиптической кривой. */
 int ak_wpoint_create_as_unit( ak_wpoint , const size_t );
/*! \brief Уничтожение данных из контекста точки эллиптической кривой. */
 int ak_wpoint_destroy( ak_wpoint );
/*! \brief Уничтожение контекста точки эллиптической кривой. */
 ak_pointer ak_wpoint_delete( ak_pointer );
/*! \brief Проверка принадлежности точки заданной кривой. */
 ak_bool ak_wpoint_is_ok( ak_wpoint , ak_wcurve );
/*! \brief Проверка порядка заданной точки. */
 ak_bool ak_wpoint_check_order( ak_wpoint , ak_wcurve );

/*! \brief Присвоение одной точке эллиптической кривой значения другой точки. */
 void ak_wpoint_set( ak_wpoint , ak_wpoint , const size_t );
/*! \brief Присвоение точке эллиптической кривой значения бесконечно удаленной точки. */
 void ak_wpoint_set_as_unit( ak_wpoint , const size_t );
/*! \brief Удвоение точки эллиптической кривой, заданной в короткой форме Вейерштрасса. */
 void ak_wpoint_double( ak_wpoint , ak_wcurve );
/*! \brief Прибавление к одной точке эллиптической кривой значения другой точки. */
 void ak_wpoint_add( ak_wpoint , ak_wpoint , ak_wcurve );
/*! \brief Приведение проективной точки к аффинному виду. */
 void ak_wpoint_reduce( ak_wpoint , ak_wcurve );
/*! \brief Вычисление кратной точки эллиптической кривой. */
 void ak_wpoint_pow( ak_wpoint , ak_wpoint , ak_uint64 *, size_t, ak_wcurve );

#endif
/* ----------------------------------------------------------------------------------------------- */
/*                                                                                    ak_curves.h  */
/* ----------------------------------------------------------------------------------------------- */
