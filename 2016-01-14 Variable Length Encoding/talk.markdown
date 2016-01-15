---
title: Variable Length Encoding
author: Roland Hieber
date: January 14, 2016
---

Problem
-------

- “I want to send a number.”
- “Well, just use 8/16/32/64 bits.”
- But what if…
	* the 64 bit range is simply not enough?
	* the required range might change in the future?
	* the required range is unknown?
	* bandwidth is low/expensive,
	  don't want to send too much unneeded data


Solutions
---------

- UTF-8
	* ISO/IEC 10646:2014
- SDNV
	* Self-Delimiting Numeric Values
	* RFC 5050, Section 4.1


UTF-8
-----

- encodes Unicode characters up to 0x7FFFFFFF
- values 0x00--0x7F are equal to 7-bit ASCII

### Encoding Rules
- Bit 8 is \textcolor{red}{\texttt{0}}: only one byte in total.
- Bit 8 is \textcolor{red}{\texttt{1}} $\Rightarrow$ more bytes to follow
	* Bit 8--7 are \texttt{\textcolor{red}{1}\textcolor{blue}{0}}: This is a following byte.
	* Bit 8--6 are \texttt{\textcolor{red}{1}\textcolor{blue}{10}}: This is a leading byte, one byte follows
	* Bit 8--5 are \texttt{\textcolor{red}{1}\textcolor{blue}{110}}: \qquad …two bytes follow
	* Bit 8--4 are \texttt{\textcolor{red}{1}\textcolor{blue}{1110}}: \qquad …three bytes follow
	* …
- “Free” bits are used to encode the value.


UTF-8: Examples
---------------

\large 
\begin{tabular}{ll}
Hex: & 0x13 \\
Binary: & \texttt{\textcolor[gray]{.8}{000}10011} \\
UTF-8: & \texttt{%
	\textcolor{red}{0}\textcolor[gray]{.8}{00}10011
}
\end{tabular}

\vfill

\begin{tabular}{ll}
Hex: & 0x1337 \\
Binary: & \texttt{\phantom{1110}\textcolor[gray]{.8}{000}1
	\phantom{10}001100 \phantom{10}110111} \\
UTF-8: & \texttt{%
	\textcolor{red}{1}\textcolor{blue}{110}\textcolor[gray]{.8}{000}1
	\textcolor{red}{1}\textcolor{blue}{0}001100
	\textcolor{red}{1}\textcolor{blue}{0}110111
}
\end{tabular}

\vfill

\begin{tabular}{ll}
Hex: & 0x31337 \\
Binary: & \texttt{%
	\phantom{11110}\textcolor[gray]{.8}{000}
	\phantom{10}110001
	\phantom{10}001100
	\phantom{10}110111
} \\
UTF-8: & \texttt{%
	\textcolor{red}{1}\textcolor{blue}{1110}\textcolor[gray]{.8}{000}
	\textcolor{red}{1}\textcolor{blue}{0}110001
	\textcolor{red}{1}\textcolor{blue}{0}001100
	\textcolor{red}{1}\textcolor{blue}{0}110111
}
\end{tabular}


SDNV
----

- specified for up to 64 bit (0xFFFFFFFF)

### Encoding Rules
- MSB is \textcolor{red}{\texttt{1}}: This is a leading byte.
- MSB is \textcolor{red}{\texttt{0}}: This is a following byte.
- “Free” bits are used to encode the value.


SDNV: Examples
--------------

\large 

\begin{tabular}{ll}
Hex: & 0x80 \\
Binary: & \texttt{\phantom{0000000}1 \phantom{0}0000000} \\
SDNV: & \texttt{%
	\textcolor{red}{1}\textcolor[gray]{0.8}{000000}1
	\textcolor{red}{0}0000000
}
\end{tabular}

\vfill

\begin{tabular}{ll}
Hex: & 0x1337 \\
Binary: & \texttt{\phantom{1}\textcolor[gray]{0.8}{0}100110 \phantom{1}0110111} \\
SDNV: & \texttt{%
	\textcolor{red}{1}\textcolor[gray]{0.8}{0}100110
	\textcolor{red}{0}0110111
}
\end{tabular}

\vfill

\begin{tabular}{ll}
Hex: & 0x31337 \\
Binary: & \texttt{\phantom{1000}1100 \phantom{1}0100110 \phantom{1}0110111} \\
SDNV: & \texttt{%
	\textcolor{red}{1}\textcolor[gray]{0.8}{000}1100
	\textcolor{red}{0}0100110
	\textcolor{red}{0}0110111
}
\end{tabular}


Comparison
----------

### UTF-8
* (+) first byte contains number of total bytes
	* (–) what about missing follow bytes?
* sync pattern: `0xxxxxxx` or `110xxxxx`

### SDNV
* sync pattern: `1xxxxxxx`

### both
* (–) susceptible against bit flips/missing bytes
