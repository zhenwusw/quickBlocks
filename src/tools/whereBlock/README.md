## whereBlock

`whereBlock` looks for and reports on the location of a block. It will return either `cache`, `node`, or `remote` depending if it finds the block in its own cache, had to go to the node to get the block, or had to go remote (because there is no node) to get the block.

If `whereBlock` return `remote` it went to Infura.

#### Usage

`Usage:`    whereBlock [-a|-v|-h] block[s]  
`Purpose:`  Reports if a block was found in the cache (and optionally its path).
             
`Where:`  

| Option | Full Command | Description |
| -------: | :------- | :------- |
|  | block[s] | a space-separated list of one or more blocks to search for |
| -a | --alone | show only the path of the block if it is found in the cache |
| -v | --verbose | set verbose level. Either -v, --verbose or -v:n where 'n' is level |
| -h | --help | display this help screen |

#### Other Options

All QuickBlocks command-line tools support the following commands (although in some case, they have no meaning):

    Command     |         Description
    -----------------------------------------------------------------------------
    --version   |   display the current version of the tool
    --nocolors  |   turn off colored display
    --wei       |   specify value in wei (the default)
    --ether     |   specify value in ether
    --dollars   |   specify value in US dollars
    --file:fn   |   specify multiple sets of command line options in a file.

*For the `--file:fn` option, place a series of valid command lines in a file and use the above option. In some cases, this option may significantly improve performance. Use semi-colon make comments.*

**Powered by QuickBlocks<sup>&reg;</sup>**


