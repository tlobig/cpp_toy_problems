# A cool warning which actually is a bug

I came across this warning when fixing warnings in a larger code base

~~~cpp
In file included from /.../abstract_factory.h:42,
                 from /.../factory_implementation.h:23,
                 from /.../does_not_even_use_it_here.cpp:12:
/.../some_state_implementation.h: In member function ‘virtual void name1::name2::SomeStateWriter::write(const name1::name3::Some_State&)’:
/.../some_state_implementation.h:90:13: warning: ‘*((void*)(&<anonymous>)+48).name1::name3::Some_other_State::color_ may be used uninitialized in this function [-Wmaybe-uninitialized]
   86 |     return color_;
~~~

or short

~~~cpp
warning: ‘*((void*)(&<anonymous>)+48).color_ may be used uninitialized in this function [-Wmaybe-uninitialized]
~~~

The **\*((void\*)(&\<anonymous\>)+48)** part looked scary. Something was off. The compiler didn't even point to the file I really needed to fix. So this was really amazing.

I painfully recreated a small toy version of this warning. When building the main.cpp in this folder with **gcc** (I did with 9.1 and 10.2) and **-O3** and **-Wall**, this time the compiler is very sure that the value is not initialized.

If you execute the unchanged program, you should be able to see that indead the ouput is not what could be expected.

If you want to tackle the problem without spoilers, just look at the main_no_spoilers.cpp

I also put this sample on godbolt to directly play with:
https://godbolt.org/z/rcMKhG

Sadly this part of the codebase has already been removed. I'm glad I could catch the warning before this gem got lost

Regards
Thomas
