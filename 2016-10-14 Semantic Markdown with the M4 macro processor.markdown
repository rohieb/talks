---
author: rohieb
date: 2016-10-14
title: Semantic Markup with the M4 macro processor
patat:
    wrap: true
    theme:
        codeBlock: [ onDullWhite ]
        code: [ onDullWhite ]
...

```






     ____                             _   _        __  __            _                  
    / ___|  ___ _ __ ___   __ _ _ __ | |_(_) ___  |  \/  | __ _ _ __| | ___   _ _ __    
    \___ \ / _ \ '_ ` _ \ / _` | '_ \| __| |/ __| | |\/| |/ _` | '__| |/ / | | | '_ \   
     ___) |  __/ | | | | | (_| | | | | |_| | (__  | |  | | (_| | |  |   <| |_| | |_) |  
    |____/ \___|_| |_| |_|\__,_|_| |_|\__|_|\___| |_|  |_|\__,_|_|  |_|\_\\__,_| .__/   
                                                                               |_|      
                              with the M4 macro processor                               






```

# M4
* Kernighan & Ritchie, 1977
  * part of almost every Unix/Linux distribution
* Heavily used in GNU `autotools`
* Simple mechanism:
    * define macros
    * when macro token is found in input, replace token with definition
    * write input to output

# Example 1: Hello World(?)
```
$ cat 01-helloworld.m4
define(HELLO, Ohai)dnl
HELLO world.
```
```
$ m4 01-helloworld.m4
Ohai world.
```

Notes:

  * `dnl`: Discard to Next Line
    * "comments"
    * prevents unwanted whitespace in output

# Example 2
```
$ cat 02-more-hello.m4
define(Nice, Happy)dnl
define(HELLO, Nice to meet you)dnl
HELLO World.
```
```
$ m4 02-more-hello.m4
Happy to meet you World.
```

What happened?

# Example 2: step by step
+----------------------------------------+---------------------------------------+
| Input                                  | Macro definitions                     |
+========================================+=======================================+
| ```                                    |                                       |
| > define(Nice, Happy)dnl               |                                       |
|   define(HELLO, Nice to meet you)dnl   |                                       |
|   HELLO World.                         |                                       |
| ```                                    |                                       |
+----------------------------------------+---------------------------------------+

# Example 2: step by step
+----------------------------------------+---------------------------------------+
| Input                                  | Macro definitions                     |
+========================================+=======================================+
| ```                                    |                                       |
| >                                      | 1. Nice → Happy                       |
|   define(HELLO, Nice to meet you)dnl   |                                       |
|   HELLO World.                         |                                       |
| ```                                    |                                       |
+----------------------------------------+---------------------------------------+

# Example 2: step by step
+----------------------------------------+---------------------------------------+
| Input                                  | Macro definitions                     |
+========================================+=======================================+
| ```                                    |                                       |
|                                        | 1. Nice → Happy                       |
| > define(HELLO, Nice to meet you)dnl   |                                       |
|   HELLO World.                         |                                       |
| ```                                    |                                       |
+----------------------------------------+---------------------------------------+

# Example 2: step by step
+----------------------------------------+---------------------------------------+
| Input                                  | Macro definitions                     |
+========================================+=======================================+
| ```                                    |                                       |
|                                        | 1. Nice → Happy                       |
| > define(HELLO, Happy to meet you)dnl  |                                       |
|   HELLO World.                         |                                       |
| ```                                    |                                       |
+----------------------------------------+---------------------------------------+

# Example 2: step by step
+----------------------------------------+---------------------------------------+
| Input                                  | Macro definitions                     |
+========================================+=======================================+
| ```                                    |                                       |
|                                        | 1. Nice → Happy                       |
| >                                      | 2. HELLO → Happy to meet you          |
|   HELLO World.                         |                                       |
| ```                                    |                                       |
+----------------------------------------+---------------------------------------+

# Example 2: step by step
+----------------------------------------+---------------------------------------+
| Input                                  | Macro definitions                     |
+========================================+=======================================+
| ```                                    |                                       |
|                                        | 1. Nice → Happy                       |
|                                        | 2. HELLO → Happy to meet you          |
| > HELLO World.                         |                                       |
| ```                                    |                                       |
+----------------------------------------+---------------------------------------+

# Example 2: step by step
+----------------------------------------+---------------------------------------+
| Input                                  | Macro definitions                     |
+========================================+=======================================+
| ```                                    |                                       |
|                                        | 1. Nice → Happy                       |
|                                        | 2. HELLO → Happy to meet you          |
| > Happy to meet you World.             |                                       |
| ```                                    |                                       |
+----------------------------------------+---------------------------------------+

# Expansion Rules (1)
1. Macro expansion is recursive
    * macros inside of macros are evaluated first (unless quoted)
    * `define` is a macro itself

But maybe we don't want that.


# Quoting
Quoting prevents unwanted macro replacement

```
$ cat 03-quoting.m4
define(`Nice', `Happy')dnl
define(`HELLO', `Nice to meet you')dnl
HELLO World.

$ m4 02-quoting.m4
Nice to meet you World.
```

# Parametric Macros
```
$ cat 04-params.m4
define(`HEADING', `<h1 id="$1">$2</h1>')dnl
define(`PARA',    `<p id="$1">$2</p>')dnl
define(`ITALIC',  `<i>$1</i>')dnl
dnl
HEADING(title, `This is the title')
PARA(first_para, This is rendered as text. Parameters can even span
multiple lines. If you include commas`,' be sure to include quotes.)
PARA(second_para, This is normal text. ITALIC(This is italic.))
```
```
$ m4 04-params.m4 
<h1 id="title">This is the title</h1>
<p id="first_para">This is rendered as text. Parameters can even span
multiple lines. If you include commas, be sure to include quotes.</p>
<p id="second_para">This is normal text. <i>This is italic.</i></p>
```

# Expansion Rules (2)
1. Quoted text is simply stripped of the quotes
2. Macro expansion is recursive
    * macros inside of macros are evaluated first (unless quoted)
        *  inner macros can generate more parameters for outer macros
3. Leading whitespace of parameters is removed
4. The expansion of a macro is always re-evaluated
    * read: "strip one layer of quoting, or expand again"

Rule of thumb:

* One quoting level per parentheses.

# You probably noticed
M4 macros are a great way to build semantic markup.

* Semantics:
    - Wikipedia: “the linguistic, and also philosophical study of meaning”
    - more than only formatting
    - ideally machine-readable

# For example
* Write your meeting minutes in Markdown, using a “public macro interface” for e.g.:
    - votes
    - resolutions
    - TODOs
* Write an M4 library for each output
    - define the “public macro interface” accordingly
* Use the markup with multiple M4 “libraries” to convert your minutes to:
    - human-readable formats like Markdown
        * with consistent formatting
        * via pandoc: HTML, ReST, LaTeX, PDF, …
    - machine-readable formats like JSON, CSV, XML, …

See: https://github.com/rohieb/minutes-m4rkup

# example.m4rkdown
```
MEETING_MINUTES(Board meeting, 2016-09-01, 20:00,
    [Adam Ant, Henrietta Horse, Beatrice Bull], [Ephraim Elephant], [Adam Ant])

We talked about things for a while.

* RESOLUTION(Resolution 2016-00, VOTE_ADOPTED(3,0,0), World Domination)
* TODO(T2016-03, Adam Ant, Build Doomsday Machine)
* Recent TODOs:
    * TODO(T2016-02, , Try out LAZZZORs from Evil Corp., [
        * They make nice, cheap LAZZZORS
        * LAZZZORS are needed for Doomsday Machine])
    * DONE(T2016-01, Beatrice Bull, Buy some space rockets)
END(21:00)
```

# example.markdown
```
Board meeting 2016-09-01
========================

* Starting time: 20:00
* Attending: Adam Ant, Henrietta Horse, Beatrice Bull
* Absent: Ephraim Elephant
* Minute taker: Adam Ant

We talked about things for a while.

* __Resolution 2016-00 ✔ (3|0|0):__ World Domination
* __TODO Adam Ant:__ Build Doomsday Machine
* Recent TODOs:
    * __TODO:__ Try out LAZZZORs from Evil Corp.. 
        * They make nice, cheap LAZZZORS
        * LAZZZORS are needed for Doomsday Machine
    * ~~__DONE Beatrice Bull:__ Buy some space rockets~~
* Ending at 21:00
```

# example.json
```
{
  "metadata": { "type": "Board meeting","date": "2016-09-01", "start_time": "20:00",
    "attendants": "Adam Ant, Henrietta Horse, Beatrice Bull",
    "absentees": "Ephraim Elephant", "keeper_of_minutes": "Adam Ant"
  },
  "content": [ 
    { "type": "resolution", "public": true, "ref": "Resolution 2016-00",
      "vote": { "approved": true, "pro": 3, "contra": 0, "abstain": 0 },
      "text": "World Domination", "allocated_money": "", "notes": ""
    },
    { "type": "todo", "public": true, "done": false, "ref": "T2016-03",
      "assigned": "Adam Ant", "text": "Build Doomsday Machine",
      "notes": "" },
    { "type": "todo", "public": true, "done": false, "ref": "T2016-02",
      "assigned": "", "text": "Try out LAZZZORs from Evil Corp.", "notes":"
  * They make nice, cheap LAZZZORS
  * LAZZZORS are needed for Doomsday Machine"
    },
    { "type": "todo", "public": true, "done": true, "ref": "T2016-01",
      "assigned": "Beatrice Bull", "text": "Buy some space rockets", "notes": ""
    }
  ],
  "end_time": "21:00"
}
```
