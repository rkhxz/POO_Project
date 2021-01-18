#include<iostream>
using namespace std;

template <class T>
class smartArray 
{
    public:
        T getValue() {
            return value;
        }
        T setValue(T value) {
            this->value = value;
        }
        int length() {
            if(!this->first) { 
                return 0; 
            }

            smartArray* currentElement = this->first;
            int elements = 1;
            while(currentElement->next) {
                elements++;
                currentElement = currentElement->next;
            }
            return elements;
        }
        smartArray get(int index) {
            if(!this->first || this->length < index || index < 0) {
                return NULL;
            }

            int currentIndex = 0;
            smartArray* currentElement = this->first;
            while(currentIndex < index && currentElement->next != NULL) {
                currentElement = currentElement->next;
            }
            return currentElement;
        }
        void remove(int index) {
            if(!this->first || this->length <= index || index < 0) {
                return;
            }

            if(index == 0) {
                smartArray* currentElement = first;
                if(!currentElement->next) {
                    delete(currentElement);
                    first = NULL;
                    last = NULL;
                    return;
                }

                currentElement = currentElement->next;
                delete(this->first);
                this->first = currentElement;
                currentElement->previous = NULL;
                return;
            }
            if(index == this->length() - 1) {
                smartArray* currentElement = last;
                if(!currentElement->previous) {
                    delete(currentElement);
                    first = NULL;
                    last = NULL;
                    return;
                }

                currentElement = currentElement->previous;
                delete(first->last);
            }
        }
        static int pula;
    private:
        /* These two are used only for the first element */
        smartArray* first = NULL;
        smartArray* last = NULL;
        /* */
        T value;
        smartArray* next;
        smartArray* previous;
};
int main() {
    smartArray<int>* cacat = new smartArray<int>();

}