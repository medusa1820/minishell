musenov@1-C-23 minishell % ./minishell
Node type: AST_NODE_PIPE
Content: (null)
Left child:
	 Node type: AST_NODE_PIPE
	 Content: (null)
	 Left child:
		  Node type: AST_NODE_PIPE
		  Content: (null)
		  Left child:
				Node type: AST_NODE_CMD
				Content:
					 Command: ls -la 
					 stdin Redirect: (null)
					 stdout Redirect: (null)
					 Assignments: (null)
				Left child:
					 Node: (null)
				Right child:
					 Node: (null)
		  Right child:
				Node type: AST_NODE_CMD
				Content:
					 Command: grep 1 
					 stdin Redirect: (null)
					 stdout Redirect: (null)
					 Assignments: (null)
				Left child:
					 Node: (null)
				Right child:
					 Node: (null)
	 Right child:
		  Node type: AST_NODE_CMD
		  Content:
				Command: wc -c 
				stdin Redirect: (null)
				stdout Redirect: (null)
				Assignments: (null)
		  Left child:
				Node: (null)
		  Right child:
				Node: (null)
Right child:
	 Node type: AST_NODE_CMD
	 Content:
		  Command: wc -l 
		  stdin Redirect: (null)
		  stdout Redirect: (null)
		  Assignments: (null)
	 Left child:
		  Node: (null)
	 Right child:
		  Node: (null)

nr_of_cmd_nodes = 0
nr_of_cmd_nodes = 1
nr_of_cmd_nodes = 2
nr_of_cmd_nodes = 3
content->cmd: ls -la 
i = 0
content->cmd: grep 1 
i = 1
content->cmd: grep 1 
i = 1
content->cmd: wc -c 
i = 2
content->cmd: wc -c 
i = 2
content->cmd: wc -c 
i = 2
content->cmd: wc -c 
i = 2
content->cmd: wc -l 
i = 3
content->cmd: wc -l 
i = 3
content->cmd: wc -l 
i = 3
content->cmd: wc -l 
i = 3
content->cmd: wc -l 
i = 3
content->cmd: wc -l 
i = 3
content->cmd: wc -l 
i = 3
content->cmd: wc -l 
i = 3