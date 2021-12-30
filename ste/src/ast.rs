pub(crate) struct StronglyTypedEnum {
    pub(crate) namespace: Vec<String>,
    pub(crate) name: String,
    pub(crate) variants: Vec<String>,
}

pub(crate) struct NamespacedIdentifier {
    pub(crate) namespace: Vec<String>,
    pub(crate) name: String,
}
