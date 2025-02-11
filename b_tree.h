#ifndef __B_TREE_H
#define __B_TREE_H

class  BlockFile;
class  BNode;
struct Result;

// -----------------------------------------------------------------------------
//  BTree: b-tree to index hash tables produced by qalsh
// -----------------------------------------------------------------------------
class BTree {
public:
	int root_;						// address of disk for root
	BNode *root_ptr_;				// pointer of root
	BlockFile *file_;				// file in disk to store
	
	// -------------------------------------------------------------------------
	BTree();						// default constructor
	~BTree();						// destructor

	// -------------------------------------------------------------------------
	void init(						// init a new b-tree
		int   b_length,					// block length
		const char *fname);				// file name	

	// -------------------------------------------------------------------------
	void init_restore(				// load an exist b-tree
		const char *fname);				// file name

	// -------------------------------------------------------------------------
	int bulkload(					// bulkload b-tree from hash table in mem
		int   n,						// number of entries
		const Result *table);			// hash table

protected:
	// -------------------------------------------------------------------------
	inline int read_header(const char *buf) { // read <root> from buffer
		memcpy(&root_, buf, SIZEINT);
		return SIZEINT;
	}

	// -------------------------------------------------------------------------
	inline int write_header(char *buf) { // write <root> into buffer
		memcpy(buf, &root_, SIZEINT);
		return SIZEINT;
	}

	// -------------------------------------------------------------------------
	inline void load_root() {		// load root of b-tree
		if (root_ptr_ == NULL) {
			root_ptr_ = new BIndexNode();
			root_ptr_->init_restore(this, root_);
		}
	}

	// -------------------------------------------------------------------------
	inline void delete_root() {		// delete root of b-tree
		if (root_ptr_ != NULL) {
			delete root_ptr_; root_ptr_ = NULL;
		}
	}
};

#endif // __B_TREE_H
