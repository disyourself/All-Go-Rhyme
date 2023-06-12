
class node:
    left_child : node
    right_child : node




 class RB_Tree:



    def get_uncle(self):
        if not self.parent or not self.parent.parent: 
            return None
        if self.parent.parent.hasBothChildrent():
            if self.parent.isLeftChild():
                return self.parent.parent.right_child
            else:
                return self.parent.parent.left_child

    def get_bother(self):
        if not self.parent: return None
        if self.parent.hasBothChildrent():
            if self.isLeftChild():
                reutrn self.parent.right_child
            else:
                return self.parent.left_child


