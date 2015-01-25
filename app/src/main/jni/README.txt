Any jobjects and jclasses created need to be released, otherwise we run the risk of overflowing
the local reference table.  We use JClass and JObject for this.