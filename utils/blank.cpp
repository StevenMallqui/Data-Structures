
 if((current1->value != current2->value) || (current1->value < current2->value)){
          current1 = current1->next;
          this->pop_front();
        }else 
          current2 = current2->next;