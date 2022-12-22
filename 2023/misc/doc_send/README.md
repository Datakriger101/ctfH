### This is an webtask. The challange is quite simple

```sh
flag:  CTFkom{h1dd3n_flag_1n_doc}

```

### Writeup

First run the **nc** command in in your cli

You will then see that you get a lot of output from the given command. But what type of text is it? You can see that there is a "=" at the end, that often indictaes that the ascii is encrypted with base64. 

I therefor run the command 

```sh
nc 174.138.12.41 3001 | base64 -d > something
```

When opening the something in a text-editor you will the that is contain data from a PFD. I therefore open the file in a document viewer. 

```sh
evince something
```

You now get a text that contain the flag
