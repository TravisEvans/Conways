//  header file for Conways
namespace Conways  {
    
    class Cell  {
        private:
            //nothing
        public:
            bool alive;
            //  vars
            //  constructors
            Cell();
            //  methods
            void setAlive();
            void setDead();
            bool getState();
    };
}