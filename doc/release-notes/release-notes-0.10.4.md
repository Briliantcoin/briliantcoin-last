Briliantcoin Core version 0.10.4 is now available from:

  <https://briliantcoin.info/bin/briliantcoin-core-0.10.4/>

This is a new minor version release, bringing security fixes and translation 
updates. It is recommended to upgrade to this version as soon as possible.

Please report bugs using the issue tracker at github:

  <https://github.com/Briliantcoin/brilantcoin/issues>

Upgrading and downgrading
=========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Briliantcoin-Qt (on Mac) or
briliantcoind/briliantcoin-qt (on Linux).

Downgrade warning
------------------

Because release 0.10.0 and later makes use of headers-first synchronization and
parallel block download (see further), the block files and databases are not
backwards-compatible with pre-0.10 versions of Briliantcoin Core or other software:

* Blocks will be stored on disk out of order (in the order they are
received, really), which makes it incompatible with some tools or
other programs. Reindexing using earlier versions will also not work
anymore as a result of this.

* The block index database will now hold headers for which no block is
stored on disk, which earlier versions won't support.

If you want to be able to downgrade smoothly, make a backup of your entire data
directory. Without this your node will need start syncing (or importing from
bootstrap.dat) anew afterwards. It is possible that the data from a completely
synchronised 0.10 node may be usable in older versions as-is, but this is not
supported and may break as soon as the older version attempts to reindex.

This does not affect wallet forward or backward compatibility.


Test for LowS signatures before relaying
-----------------------------------------

Make the node require the canonical 'low-s' encoding for ECDSA signatures when
relaying or mining.  This removes a nuisance malleability vector.

Consensus behavior is unchanged.

If widely deployed this change would eliminate the last remaining known vector
for nuisance malleability on SIGHASH_ALL P2PKH transactions. On the down-side
it will block most transactions made by sufficiently out of date software.

Unlike the other avenues to change txids on transactions this
one was randomly violated by all deployed briliantcoin software prior to
its discovery. So, while other malleability vectors where made
non-standard as soon as they were discovered, this one has remained
permitted. Even BIP62 did not propose applying this rule to
old version transactions, but conforming implementations have become
much more common since BIP62 was initially written.

Briliantcoin Core has produced compatible signatures since a28fb70e in
September 2013, but this didn't make it into a release until 0.9
in March 2014; Briliantcoinj has done so for a similar span of time.
Briliantcoinjs and electrum have been more recently updated.

This does not replace the need for BIP62 or similar, as miners can
still cooperate to break transactions.  Nor does it replace the
need for wallet software to handle malleability sanely[1]. This
only eliminates the cheap and irritating DOS attack.

[1] On the Malleability of Briliantcoin Transactions
Marcin Andrychowicz, Stefan Dziembowski, Daniel Malinowski, Łukasz Mazurek
http://fc15.ifca.ai/preproceedings/briliantcoin/paper_9.pdf

Minimum relay fee default increase
-----------------------------------

The default for the `-minrelaytxfee` setting has been increased from `0.00001`
to `0.00005`.

This is necessitated by the current transaction flooding, causing
outrageous memory usage on nodes due to the mempool ballooning. This is a
temporary measure, bridging the time until a dynamic method for determining
this fee is merged (which will be in 0.12).

(see https://github.com/Briliantcoin/briliantcoin/pull/6793, as well as the 0.11.0
release notes, in which this value was suggested)

As well as everyone that helped translating on [Transifex](https://www.transifex.com/projects/p/briliantcoin/).
