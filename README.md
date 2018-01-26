# What is this?

This project is meant to develop a Flashcard program using Qt5.10,
it reads .deck files from the res folder, which are JSON documents formatted
in a specific way.

# How do I format the .deck file

There will be an inbuilt .deck editor, that supports to/from CSV conversion.

Here is an example, taken from *test_pos.deck*, see below, for explanation
```
{
    "Properties": {
        "Title" : "Elementary 1"
    },
    "Words": {
        "1" : [
            ["english","apple"],
            ["chinese","苹果"],
            ["pinyin","ping2 guo3"]
        ],

        "2" : [
            ["english","table"],
            ["chinese","桌子"],
            ["pinyin","zhuo1 zi0"]
        ],
		
		"3" : [
            ["english","table"],
            ["hungarian","asztal"]
        ]
    }
}
```

Every .deck file should contain exactly 2 objects (aside from the root).
These are with the respective keys `Properties` and `Words`.
The JSON Object `Properties` contains information about the deck itself.
The JSON Object `Words` contain the actual words, the JSON Objects with numbers
will be converted into `CF::Flashcard objects`, which contain `CF::Words`,
created from the JSON Arrays the numbered keys point to.
Each `CF::Flashcard` object can contain any number of `CF::Words` inside them.
`CF::Words` are made up of a language and word pair.

Flashcards are designed this way, to provide support for languages such as Chinese,
that require more than 2 words.

# How do I build this?

## Get the Qt sources

You need the original Qt libraries to build this project.
Get the Qt sources at: [Sources](http://download.qt.io/official_releases/qt/5.10/5.10.0/single/)
alternatively get the Qt Editor: [Qt Editor](https://www.qt.io/download-qt-installer)

## To build

Open the CuteCards.pro file in **Qt Editor**.

Under **Build Steps** add **Build Step -> Custom Process Step** 
add two of them.

##### Unix:

1
* Command: `cp`
* Arguments: `-r %{sourceDir}\res_test %{buildDir}\CuteCards_test\` 
* Working d...: `%{buildDir}`
   
2
* Command: `cp`
* Arguments: `-r %{sourceDir}\res_main %{buildDir}\CuteCards_main\` 
* Working d...: `%{buildDir}`


##### Windows:

1
* Command: `xcopy`
* Arguments: `/E /Y %{sourceDir}\res_test %{buildDir}\CuteCards_test\` 
* Working d...: `%{buildDir}`


2
* Command: `xcopy`
* Arguments: `/E /Y %{sourceDir}\res_main %{buildDir}\CuteCards_main\` 
* Working d...: `%{buildDir}`



This is needed to ensure that the files in res_test and res_main gets copied into the build directories.

## Qmake

Or you can choose to build the project with **qmake**
You may have to change the variables `QMAKESPEC` and `PATH`. See [qmake Variables](http://doc.qt.io/qt-5/qmake-variable-reference.html) for details.

`qmake -makefile <PATH_TO_PRO_FILE>/CuteCards.pro`

`cp -r <PATH_TO_PRO_FILE>/CuteCards/res_test <PATH_TO_BUILD>/CuteCards_test/`

`cp -r <PATH_TO_PRO_FILE>/CuteCards/res_main <PATH_TO_BUILD>/CuteCards_main/`

# License

This project made public under the terms of GNU GPL, see LICENSE for details.
More at [gnu.org/licenses/gpl-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)
