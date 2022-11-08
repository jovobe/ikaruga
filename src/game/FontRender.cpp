#include "FontRender.hpp"
#include <list>

using std::string;
using std::vector;

namespace ikaruga
{

    FontRender::FontRender(int tileHeight,
                           int tileWidth,
                           SDL_Renderer* renderer,
                           SDL_Texture* texture) : StaticRenderable(renderer, texture)
    {
        m_tileHeight = tileHeight;
        m_tileWidth = tileWidth;
    }

    vector<Vector2i> FontRender::renderNumber(int number, int numberOffset)
    {
        vector<Vector2i> retVal;
        std::list<int> digits;

        if (0 == number)
        {
            digits.push_back(10);
        }
        else
        {
            while (number != 0)
            {
                int last = number % 10;
                digits.push_front(last);
                number = (number - last) / 10;
            }
        }

        for (std::list<int>::iterator it = digits.begin(); it != digits.end(); it++)
        {
            int num;
            if (*it == 0)
            {
                num = 10 - 1;
            }
            else
            {
                num = *it - 1;
            }
            Vector2i source;
            source.setX(num * m_tileWidth);
            source.setY(numberOffset);
            retVal.push_back(source);
        }
        return retVal;
    }

    vector<Vector2i> FontRender::renderString(string str, int minusculeOffset, int capitalOffset, int numberOffset)
    {
        vector<Vector2i> retVal;
        for (unsigned int i = 0; i < str.length(); i++)
        {
            Vector2i source_vec;
            string strLetter = string(1, str[i]);
            string strLetterToUpper = str;
            bool upperCase = false;
            int height_offset = 0;
            //check for whitespace
            if (str == " ")
            {
                //We don't ever have the 10 as a number, so 10 should be a Whitespace
                source_vec.setX(10 * m_tileWidth);
                source_vec.setY(numberOffset * m_tileHeight);
            }
            else
            {
                //check for casing
                std::transform(strLetterToUpper.begin(),
                               strLetterToUpper.end(),
                               strLetterToUpper.begin(),
                               ::toupper);
                strLetterToUpper = string(1, strLetterToUpper[i]);
                if (strLetterToUpper == strLetter)
                {
                    upperCase = true;
                    height_offset = capitalOffset;
                }
                else
                {
                    upperCase = false;
                    height_offset = minusculeOffset;
                }
                int character_index = 0;
                //calculate letter number in the alphabet, minus 1, because offset
                const char* cha = strLetter.c_str();
                if (upperCase)
                {
                    character_index = int(*cha) - 48 - 17;
                }
                else
                {
                    character_index = int(*cha) - 48 - 23 - 26;
                }
                source_vec.setX(character_index * m_tileWidth);
                source_vec.setY(height_offset * m_tileHeight);
            }
            retVal.push_back(source_vec);
        }
        return retVal;
    }
} /* namespace ikaruga */
