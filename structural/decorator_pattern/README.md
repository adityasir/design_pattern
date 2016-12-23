# decorator design_pattern

The classical definition of decorator design patter are as below :

* Attach additional responsibilities to an object dynamically.
        Decorators provide a flexible alternative to subclassing for extending functionality. [GoF, p175]

* Decorator pattern allows us to add new functionality to an existing object without altering its structure.


From above definition it is clear that decorator design patter provides a solution to empower an existing 
 object to perform multifarious activity DYNAMICALLY.

Sometime we don't want any performance penalty introduced by run time dynamic polymorphism.                                 
And for me it make sense why could baby will have pain once she will born, pain only should be at labor
 room means compile time.

Compile time means, static polymorphism, using template. 

In this example, I have tried to empower HumanFilter object to perform different activity on the basis of
FilterCriteria object parameter passed to it. 

This solution also fits with Open/Close principles of software development. 
Once the filter class is written, i.e HumanFilter it do not required to change or even modified, only new 
criteria need to be added for each new search criteria. 

Compile:
g++ -std=c++11 decorator_pattern.cpp


output:


 -->Empower human_filter to filter by cricket playing country <--

	Asian is cricket playing country.

	Australia is cricket playing country.

 -->Empower human_filter to filter by colorimentry criteria <--

	European are white color human.

	Australia are white color human.

 -->Empower human_filter to filter by cricket plyaing country and colorimentry criteria <--

	Australia are white color cricket playing human.

