//
//  jr_array.h
//  SwiftDown
//
//  Created by 王潇 on 2017/3/14.
//  Copyright © 2017年 王潇. All rights reserved.
//

#ifndef jr_array_h
#define jr_array_h
/// A contiguously stored array.
///
/// The `ContiguousArray` type is a specialized array that always stores its
/// elements in a contiguous region of memory. This contrasts with `Array`,
/// which can store its elements in either a contiguous region of memory or an
/// `NSArray` instance if its `Element` type is a class or `@objc` protocol.
///
/// If your array's `Element` type is a class or `@objc` protocol and you do
/// not need to bridge the array to `NSArray` or pass the array to Objective-C
/// APIs, using `ContiguousArray` may be more efficient and have more
/// predictable performance than `Array`. If the array's `Element` type is a
/// struct or enumeration, `Array` and `ContiguousArray` should have similar
/// efficiency.
///
/// For more information about using arrays, see `Array` and `ArraySlice`, with
/// which `ContiguousArray` shares most properties and methods.
public struct ContiguousArray<Element> : RandomAccessCollection, MutableCollection {
	
	/// A type that represents a position in the collection.
	///
	/// Valid indices consist of the position of every element and a
	/// "past the end" position that's not valid for use as a subscript
	/// argument.
	///
	/// - SeeAlso: endIndex
	public typealias Index = Int
	
	/// A type that provides the collection's iteration interface and
	/// encapsulates its iteration state.
	///
	/// By default, a collection conforms to the `Sequence` protocol by
	/// supplying a `IndexingIterator` as its associated `Iterator`
	/// type.
	public typealias Iterator = IndexingIterator<ContiguousArray<Element>>
	
	/// The position of the first element in a nonempty array.
	///
	/// For an instance of `ContiguousArray`, `startIndex` is always zero. If the array
	/// is empty, `startIndex` is equal to `endIndex`.
	public var startIndex: Int { get }
	
	/// The array's "past the end" position---that is, the position one greater
	/// than the last valid subscript argument.
	///
	/// When you need a range that includes the last element of an array, use the
	/// half-open range operator (`..<`) with `endIndex`. The `..<` operator
	/// creates a range that doesn't include the upper bound, so it's always
	/// safe to use with `endIndex`. For example:
	///
	///     let numbers = [10, 20, 30, 40, 50]
	///     if let i = numbers.index(of: 30) {
	///         print(numbers[i ..< numbers.endIndex])
	///     }
	///     // Prints "[30, 40, 50]"
	///
	/// If the array is empty, `endIndex` is equal to `startIndex`.
	public var endIndex: Int { get }
	
	/// Returns the position immediately after the given index.
	///
	/// - Parameter i: A valid index of the collection. `i` must be less than
	///   `endIndex`.
	/// - Returns: The index value immediately after `i`.
	public func index(after i: Int) -> Int
	
	/// Replaces the given index with its successor.
	///
	/// - Parameter i: A valid index of the collection. `i` must be less than
	///   `endIndex`.
	public func formIndex(after i: inout Int)
	
	/// Returns the position immediately before the given index.
	///
	/// - Parameter i: A valid index of the collection. `i` must be greater than
	///   `startIndex`.
	/// - Returns: The index value immediately before `i`.
	public func index(before i: Int) -> Int
	
	/// Replaces the given index with its predecessor.
	///
	/// - Parameter i: A valid index of the collection. `i` must be greater than
	///   `startIndex`.
	public func formIndex(before i: inout Int)
	
	/// Returns an index that is the specified distance from the given index.
	///
	/// The following example obtains an index advanced four positions from an
	/// array's starting index and then prints the element at that position.
	///
	///     let numbers = [10, 20, 30, 40, 50]
	///     let i = numbers.index(numbers.startIndex, offsetBy: 4)
	///     print(numbers[i])
	///     // Prints "50"
	///
	/// Advancing an index beyond a collection's ending index or offsetting it
	/// before a collection's starting index may trigger a runtime error. The
	/// value passed as `n` must not result in such an operation.
	///
	/// - Parameters:
	///   - i: A valid index of the array.
	///   - n: The distance to offset `i`.
	/// - Returns: An index offset by `n` from the index `i`. If `n` is positive,
	///   this is the same value as the result of `n` calls to `index(after:)`.
	///   If `n` is negative, this is the same value as the result of `-n` calls
	///   to `index(before:)`.
	///
	/// - Complexity: O(1)
	public func index(_ i: Int, offsetBy n: Int) -> Int
	
	/// Returns an index that is the specified distance from the given index,
	/// unless that distance is beyond a given limiting index.
	///
	/// The following example obtains an index advanced four positions from an
	/// array's starting index and then prints the element at that position. The
	/// operation doesn't require going beyond the limiting `numbers.endIndex`
	/// value, so it succeeds.
	///
	///     let numbers = [10, 20, 30, 40, 50]
	///     let i = numbers.index(numbers.startIndex,
	///                           offsetBy: 4,
	///                           limitedBy: numbers.endIndex)
	///     print(numbers[i])
	///     // Prints "50"
	///
	/// The next example attempts to retrieve an index ten positions from
	/// `numbers.startIndex`, but fails, because that distance is beyond the
	/// index passed as `limit`.
	///
	///     let j = numbers.index(numbers.startIndex,
	///                           offsetBy: 10,
	///                           limitedBy: numbers.endIndex)
	///     print(j)
	///     // Prints "nil"
	///
	/// Advancing an index beyond a collection's ending index or offsetting it
	/// before a collection's starting index may trigger a runtime error. The
	/// value passed as `n` must not result in such an operation.
	///
	/// - Parameters:
	///   - i: A valid index of the array.
	///   - n: The distance to offset `i`.
	///   - limit: A valid index of the collection to use as a limit. If `n > 0`,
	///     `limit` has no effect if it is less than `i`. Likewise, if `n < 0`,
	///     `limit` has no effect if it is greater than `i`.
	/// - Returns: An index offset by `n` from the index `i`, unless that index
	///   would be beyond `limit` in the direction of movement. In that case,
	///   the method returns `nil`.
	///
	/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
	/// - Complexity: O(1)
	public func index(_ i: Int, offsetBy n: Int, limitedBy limit: Int) -> Int?
	
	/// Returns the distance between two indices.
	///
	/// - Parameters:
	///   - start: A valid index of the collection.
	///   - end: Another valid index of the collection. If `end` is equal to
	///     `start`, the result is zero.
	/// - Returns: The distance between `start` and `end`.
	public func distance(from start: Int, to end: Int) -> Int
	
	/// A type that can represent the indices that are valid for subscripting the
	/// collection, in ascending order.
	public typealias Indices = CountableRange<Int>
	
	/// Accesses the element at the specified position.
	///
	/// The following example uses indexed subscripting to update an array's
	/// second element. After assigning the new value (`"Butler"`) at a specific
	/// position, that value is immediately available at that same position.
	///
	///     var streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     streets[1] = "Butler"
	///     print(streets[1])
	///     // Prints "Butler"
	///
	/// - Parameter index: The position of the element to access. `index` must be
	///   greater than or equal to `startIndex` and less than `endIndex`.
	///
	/// - Complexity: Reading an element from an array is O(1). Writing is O(1)
	///   unless the array's storage is shared with another array, in which case
	///   writing is O(*n*), where *n* is the length of the array.
	public subscript(index: Int) -> Element
	
	/// Accesses a contiguous subrange of the array's elements.
	///
	/// The returned `ArraySlice` instance uses the same indices for the same
	/// elements as the original array. In particular, that slice, unlike an
	/// array, may have a nonzero `startIndex` and an `endIndex` that is not
	/// equal to `count`. Always use the slice's `startIndex` and `endIndex`
	/// properties instead of assuming that its indices start or end at a
	/// particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let i = streetsSlice.index(of: "Evarts")    // 4
	///     print(streets[i!])
	///     // Prints "Evarts"
	///
	/// - Parameter bounds: A range of integers. The bounds of the range must be
	///   valid indices of the array.
	///
	/// - SeeAlso: `ArraySlice`
	public subscript(bounds: Range<Int>) -> ArraySlice<Element>
	
	/// Calls a closure with a pointer to the array's contiguous storage.
	///
	///
	/// Often, the optimizer can eliminate bounds checks within an array
	/// algorithm, but when that fails, invoking the same algorithm on the
	/// buffer pointer passed into your closure lets you trade safety for speed.
	///
	/// The following example shows how you can iterate over the contents of the
	/// buffer pointer:
	///
	///     let numbers = [1, 2, 3, 4, 5]
	///     let sum = numbers.withUnsafeBufferPointer { buffer -> Int in
	///         var result = 0
	///         for i in stride(from: buffer.startIndex, to: buffer.endIndex, by: 2) {
	///             result += buffer[i]
	///         }
	///         return result
	///     }
	///     // 'sum' == 9
	///
	/// - Parameter body: A closure with an `UnsafeBufferPointer` parameter that
	///   points to the contiguous storage for the array. If `body` has a return
	///   value, it is used as the return value for the
	///   `withUnsafeBufferPointer(_:)` method. The pointer argument is valid
	///   only for the duration of the closure's execution.
	/// - Returns: The return value of the `body` closure parameter, if any.
	///
	/// - SeeAlso: `withUnsafeMutableBufferPointer`, `UnsafeBufferPointer`
	public func withUnsafeBufferPointer<R>(_ body: (UnsafeBufferPointer<Element>) throws -> R) rethrows -> R
	
	/// Calls the given closure with a pointer to the array's mutable contiguous
	/// storage.
	///
	/// Often, the optimizer can eliminate bounds checks within an array
	/// algorithm, but when that fails, invoking the same algorithm on the
	/// buffer pointer passed into your closure lets you trade safety for speed.
	///
	/// The following example shows modifying the contents of the
	/// `UnsafeMutableBufferPointer` argument to `body` alters the contents of
	/// the array:
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     numbers.withUnsafeMutableBufferPointer { buffer in
	///         for i in stride(from: buffer.startIndex, to: buffer.endIndex - 1, by: 2) {
	///             swap(&buffer[i], &buffer[i + 1])
	///         }
	///     }
	///     print(numbers)
	///     // Prints "[2, 1, 4, 3, 5]"
	///
	/// - Warning: Do not rely on anything about `self` (the array that is the
	///   target of this method) during the execution of the `body` closure: It
	///   may not appear to have its correct value.  Instead, use only the
	///   `UnsafeMutableBufferPointer` argument to `body`.
	///
	/// - Parameter body: A closure with an `UnsafeMutableBufferPointer`
	///   parameter that points to the contiguous storage for the array. If
	///   `body` has a return value, it is used as the return value for the
	///   `withUnsafeMutableBufferPointer(_:)` method. The pointer argument is
	///   valid only for the duration of the closure's execution.
	/// - Returns: The return value of the `body` closure parameter, if any.
	///
	/// - SeeAlso: `withUnsafeBufferPointer`, `UnsafeMutableBufferPointer`
	public mutating func withUnsafeMutableBufferPointer<R>(_ body: (inout UnsafeMutableBufferPointer<Element>) throws -> R) rethrows -> R
	
	/// Replaces a range of elements with the elements in the specified
	/// collection.
	///
	/// This method has the effect of removing the specified range of elements
	/// from the array and inserting the new elements at the same location. The
	/// number of new elements need not match the number of elements being
	/// removed.
	///
	/// In this example, three elements in the middle of an array of integers are
	/// replaced by the five elements of a `Repeated<Int>` instance.
	///
	///      var nums = [10, 20, 30, 40, 50]
	///      nums.replaceSubrange(1...3, with: repeatElement(1, count: 5))
	///      print(nums)
	///      // Prints "[10, 1, 1, 1, 1, 1, 50]"
	///
	/// If you pass a zero-length range as the `subrange` parameter, this method
	/// inserts the elements of `newElements` at `subrange.startIndex`. Calling
	/// the `insert(contentsOf:at:)` method instead is preferred.
	///
	/// Likewise, if you pass a zero-length collection as the `newElements`
	/// parameter, this method removes the elements in the given subrange
	/// without replacement. Calling the `removeSubrange(_:)` method instead is
	/// preferred.
	///
	/// - Parameters:
	///   - subrange: The subrange of the array to replace. The start and end of
	///     a subrange must be valid indices of the array.
	///   - newElements: The new elements to add to the array.
	///
	/// - Complexity: O(`subrange.count`) if you are replacing a suffix of the
	///   array with an empty collection; otherwise, O(*n*), where *n* is the
	///   length of the array.
	public mutating func replaceSubrange<C where C : Collection, C.Iterator.Element == _Buffer.Element>(_ subrange: Range<Int>, with newElements: C)
	
	/// Calls a closure with a view of the array's underlying bytes of memory as a
	/// Collection of `UInt8`.
	///
	///  If no such storage exists, it is first created.
	///
	/// - Precondition: `Pointee` is a trivial type.
	///
	/// The following example shows how you copy bytes into an array:
	///
	///    var numbers = [Int32](repeating: 0, count: 2)
	///    var byteValues: [UInt8] = [0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00]
	///    numbers.withUnsafeMutableBytes { destBytes in
	///      byteValues.withUnsafeBytes { srcBytes in
	///        destBytes.copyBytes(from: srcBytes)
	///      }
	///    }
	///
	/// - Parameter body: A closure with an `UnsafeRawBufferPointer`
	///   parameter that points to the contiguous storage for the array. If `body`
	///   has a return value, it is used as the return value for the
	///   `withUnsafeMutableBytes(_:)` method. The argument is valid only for the
	///   duration of the closure's execution.
	/// - Returns: The return value of the `body` closure parameter, if any.
	///
	/// - SeeAlso: `withUnsafeBytes`, `UnsafeMutableRawBufferPointer`
	public mutating func withUnsafeMutableBytes<R>(_ body: (UnsafeMutableRawBufferPointer) throws -> R) rethrows -> R
	
	/// Calls a closure with a view of the array's underlying bytes of memory
	/// as a Collection of `UInt8`.
	///
	///  If no such storage exists, it is first created.
	///
	/// - Precondition: `Pointee` is a trivial type.
	///
	/// The following example shows how you copy the contents of an array into a
	/// buffer of `UInt8`:
	///
	///    let numbers = [1, 2, 3]
	///    var byteBuffer = [UInt8]()
	///    numbers.withUnsafeBytes {
	///        byteBuffer += $0
	///    }
	///
	/// - Parameter body: A closure with an `UnsafeRawBufferPointer` parameter
	///   that points to the contiguous storage for the array. If `body` has a
	///   return value, it is used as the return value for the
	///   `withUnsafeBytes(_:)` method. The argument is valid only for the
	///   duration of the closure's execution.
	/// - Returns: The return value of the `body` closure parameter, if any.
	///
	/// - SeeAlso: `withUnsafeBytes`, `UnsafeRawBufferPointer`
	public func withUnsafeBytes<R>(_ body: (UnsafeRawBufferPointer) throws -> R) rethrows -> R
	
	/// Removes and returns the last element of the array.
	///
	/// - Returns: The last element of the array if the array is not empty;
	///   otherwise, `nil`.
	///
	/// - Complexity: O(1)
	/// - SeeAlso: `removeLast()`
	public mutating func popLast() -> Element?
	
	/// Returns a subsequence containing all but the specified number of final
	/// elements.
	///
	/// If the number of elements to drop exceeds the number of elements in the
	/// collection, the result is an empty subsequence.
	///
	///     let numbers = [1, 2, 3, 4, 5]
	///     print(numbers.dropLast(2))
	///     // Prints "[1, 2, 3]"
	///     print(numbers.dropLast(10))
	///     // Prints "[]"
	///
	/// - Parameter n: The number of elements to drop off the end of the
	///   collection. `n` must be greater than or equal to zero.
	/// - Returns: A subsequence that leaves off `n` elements from the end.
	///
	/// - Complexity: O(*n*), where *n* is the number of elements to drop.
	public func dropLast(_ n: Int) -> ArraySlice<Element>
	
	/// Returns a subsequence, up to the given maximum length, containing the
	/// final elements of the collection.
	///
	/// If the maximum length exceeds the number of elements in the collection,
	/// the result contains the entire collection.
	///
	///     let numbers = [1, 2, 3, 4, 5]
	///     print(numbers.suffix(2))
	///     // Prints "[4, 5]"
	///     print(numbers.suffix(10))
	///     // Prints "[1, 2, 3, 4, 5]"
	///
	/// - Parameter maxLength: The maximum number of elements to return.
	///   `maxLength` must be greater than or equal to zero.
	/// - Returns: A subsequence terminating at the end of the collection with at
	///   most `maxLength` elements.
	///
	/// - Complexity: O(*n*), where *n* is equal to `maxLength`.
	public func suffix(_ maxLength: Int) -> ArraySlice<Element>
	
	/// Returns an array containing the results of mapping the given closure
	/// over the sequence's elements.
	///
	/// In this example, `map` is used first to convert the names in the array
	/// to lowercase strings and then to count their characters.
	///
	///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
	///     let lowercaseNames = cast.map { $0.lowercaseString }
	///     // 'lowercaseNames' == ["vivien", "marlon", "kim", "karl"]
	///     let letterCounts = cast.map { $0.characters.count }
	///     // 'letterCounts' == [6, 6, 3, 4]
	///
	/// - Parameter transform: A mapping closure. `transform` accepts an
	///   element of this sequence as its parameter and returns a transformed
	///   value of the same or of a different type.
	/// - Returns: An array containing the transformed elements of this
	///   sequence.
	public func map<T>(_ transform: (Element) throws -> T) rethrows -> [T]
	
	/// Returns a subsequence containing all but the given number of initial
	/// elements.
	///
	/// If the number of elements to drop exceeds the number of elements in
	/// the collection, the result is an empty subsequence.
	///
	///     let numbers = [1, 2, 3, 4, 5]
	///     print(numbers.dropFirst(2))
	///     // Prints "[3, 4, 5]"
	///     print(numbers.dropFirst(10))
	///     // Prints "[]"
	///
	/// - Parameter n: The number of elements to drop from the beginning of
	///   the collection. `n` must be greater than or equal to zero.
	/// - Returns: A subsequence starting after the specified number of
	///   elements.
	///
	/// - Complexity: O(*n*), where *n* is the number of elements to drop from
	///   the beginning of the collection.
	public func dropFirst(_ n: Int) -> ArraySlice<Element>
	
	/// Returns a subsequence, up to the specified maximum length, containing
	/// the initial elements of the collection.
	///
	/// If the maximum length exceeds the number of elements in the collection,
	/// the result contains all the elements in the collection.
	///
	///     let numbers = [1, 2, 3, 4, 5]
	///     print(numbers.prefix(2))
	///     // Prints "[1, 2]"
	///     print(numbers.prefix(10))
	///     // Prints "[1, 2, 3, 4, 5]"
	///
	/// - Parameter maxLength: The maximum number of elements to return.
	///   `maxLength` must be greater than or equal to zero.
	/// - Returns: A subsequence starting at the beginning of this collection
	///   with at most `maxLength` elements.
	public func prefix(_ maxLength: Int) -> ArraySlice<Element>
	
	/// Returns a subsequence from the start of the collection up to, but not
	/// including, the specified position.
	///
	/// The resulting subsequence *does not include* the element at the position
	/// `end`. The following example searches for the index of the number `40`
	/// in an array of integers, and then prints the prefix of the array up to,
	/// but not including, that index:
	///
	///     let numbers = [10, 20, 30, 40, 50, 60]
	///     if let i = numbers.index(of: 40) {
	///         print(numbers.prefix(upTo: i))
	///     }
	///     // Prints "[10, 20, 30]"
	///
	/// Passing the collection's starting index as the `end` parameter results in
	/// an empty subsequence.
	///
	///     print(numbers.prefix(upTo: numbers.startIndex))
	///     // Prints "[]"
	///
	/// - Parameter end: The "past the end" index of the resulting subsequence.
	///   `end` must be a valid index of the collection.
	/// - Returns: A subsequence up to, but not including, the `end` position.
	///
	/// - Complexity: O(1)
	/// - SeeAlso: `prefix(through:)`
	public func prefix(upTo end: Int) -> ArraySlice<Element>
	
	/// Returns a subsequence from the specified position to the end of the
	/// collection.
	///
	/// The following example searches for the index of the number `40` in an
	/// array of integers, and then prints the suffix of the array starting at
	/// that index:
	///
	///     let numbers = [10, 20, 30, 40, 50, 60]
	///     if let i = numbers.index(of: 40) {
	///         print(numbers.suffix(from: i))
	///     }
	///     // Prints "[40, 50, 60]"
	///
	/// Passing the collection's `endIndex` as the `start` parameter results in
	/// an empty subsequence.
	///
	///     print(numbers.suffix(from: numbers.endIndex))
	///     // Prints "[]"
	///
	/// - Parameter start: The index at which to start the resulting subsequence.
	///   `start` must be a valid index of the collection.
	/// - Returns: A subsequence starting at the `start` position.
	///
	/// - Complexity: O(1)
	public func suffix(from start: Int) -> ArraySlice<Element>
	
	/// Returns a subsequence from the start of the collection through the
	/// specified position.
	///
	/// The resulting subsequence *includes* the element at the position `end`.
	/// The following example searches for the index of the number `40` in an
	/// array of integers, and then prints the prefix of the array up to, and
	/// including, that index:
	///
	///     let numbers = [10, 20, 30, 40, 50, 60]
	///     if let i = numbers.index(of: 40) {
	///         print(numbers.prefix(through: i))
	///     }
	///     // Prints "[10, 20, 30, 40]"
	///
	/// - Parameter end: The index of the last element to include in the
	///   resulting subsequence. `end` must be a valid index of the collection
	///   that is not equal to the `endIndex` property.
	/// - Returns: A subsequence up to, and including, the `end` position.
	///
	/// - Complexity: O(1)
	/// - SeeAlso: `prefix(upTo:)`
	public func prefix(through position: Int) -> ArraySlice<Element>
	
	/// Returns the longest possible subsequences of the collection, in order,
	/// that don't contain elements satisfying the given predicate.
	///
	/// The resulting array consists of at most `maxSplits + 1` subsequences.
	/// Elements that are used to split the sequence are not returned as part of
	/// any subsequence.
	///
	/// The following examples show the effects of the `maxSplits` and
	/// `omittingEmptySubsequences` parameters when splitting a string using a
	/// closure that matches spaces. The first use of `split` returns each word
	/// that was originally separated by one or more spaces.
	///
	///     let line = "BLANCHE:   I don't want realism. I want magic!"
	///     print(line.characters.split(whereSeparator: { $0 == " " })
	///                          .map(String.init))
	///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
	///
	/// The second example passes `1` for the `maxSplits` parameter, so the
	/// original string is split just once, into two new strings.
	///
	///     print(
	///         line.characters.split(
	///             maxSplits: 1, whereSeparator: { $0 == " " }
	///             ).map(String.init))
	///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
	///
	/// The final example passes `false` for the `omittingEmptySubsequences`
	/// parameter, so the returned array contains empty strings where spaces
	/// were repeated.
	///
	///     print(line.characters.split(omittingEmptySubsequences: false, whereSeparator: { $0 == " " })
	///                           .map(String.init))
	///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
	///
	/// - Parameters:
	///   - maxSplits: The maximum number of times to split the collection, or
	///     one less than the number of subsequences to return. If
	///     `maxSplits + 1` subsequences are returned, the last one is a suffix
	///     of the original collection containing the remaining elements.
	///     `maxSplits` must be greater than or equal to zero. The default value
	///     is `Int.max`.
	///   - omittingEmptySubsequences: If `false`, an empty subsequence is
	///     returned in the result for each pair of consecutive elements
	///     satisfying the `isSeparator` predicate and for each element at the
	///     start or end of the collection satisfying the `isSeparator`
	///     predicate. The default value is `true`.
	///   - isSeparator: A closure that takes an element as an argument and
	///     returns a Boolean value indicating whether the collection should be
	///     split at that element.
	/// - Returns: An array of subsequences, split from this collection's
	///   elements.
	public func split(maxSplits: Int = default, omittingEmptySubsequences: Bool = default, whereSeparator isSeparator: (Element) throws -> Bool) rethrows -> [ArraySlice<Element>]
	
	/// The last element of the collection.
	///
	/// If the collection is empty, the value of this property is `nil`.
	///
	///     let numbers = [10, 20, 30, 40, 50]
	///     if let lastNumber = numbers.last {
	///         print(lastNumber)
	///     }
	///     // Prints "50"
	public var last: Element? { get }
	
	/// Returns the first index in which an element of the collection satisfies
	/// the given predicate.
	///
	/// You can use the predicate to find an element of a type that doesn't
	/// conform to the `Equatable` protocol or to find an element that matches
	/// particular criteria. Here's an example that finds a student name that
	/// begins with the letter "A":
	///
	///     let students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
	///     if let i = students.index(where: { $0.hasPrefix("A") }) {
	///         print("\(students[i]) starts with 'A'!")
	///     }
	///     // Prints "Abena starts with 'A'!"
	///
	/// - Parameter predicate: A closure that takes an element as its argument
	///   and returns a Boolean value that indicates whether the passed element
	///   represents a match.
	/// - Returns: The index of the first element for which `predicate` returns
	///   `true`. If no elements in the collection satisfy the given predicate,
	///   returns `nil`.
	///
	/// - SeeAlso: `index(of:)`
	public func index(where predicate: (Element) throws -> Bool) rethrows -> Int?
	
	public mutating func partition(by belongsInSecondPartition: (Element) throws -> Bool) rethrows -> Int
	
	public mutating func partition(by belongsInSecondPartition: (Element) throws -> Bool) rethrows -> Int
	
	/// Returns the elements of the collection, sorted using the given
	/// predicate as the comparison between elements.
	///
	/// When you want to sort a collection of elements that don't conform to
	/// the `Comparable` protocol, pass a predicate to this method that returns
	/// `true` when the first element passed should be ordered before the
	/// second. The elements of the resulting array are ordered according to the
	/// given predicate.
	///
	/// The predicate must be a *strict weak ordering* over the elements. That
	/// is, for any elements `a`, `b`, and `c`, the following conditions must
	/// hold:
	///
	/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
	/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
	///   both `true`, then `areInIncreasingOrder(a, c)` is also `true`.
	///   (Transitive comparability)
	/// - Two elements are *incomparable* if neither is ordered before the other
	///   according to the predicate. If `a` and `b` are incomparable, and `b`
	///   and `c` are incomparable, then `a` and `c` are also incomparable.
	///   (Transitive incomparability)
	///
	/// The sorting algorithm is not stable. A nonstable sort may change the
	/// relative order of elements for which `areInIncreasingOrder` does not
	/// establish an order.
	///
	/// In the following example, the predicate provides an ordering for an array
	/// of a custom `HTTPResponse` type. The predicate orders errors before
	/// successes and sorts the error responses by their error code.
	///
	///     enum HTTPResponse {
	///         case ok
	///         case error(Int)
	///     }
	///
	///     let responses: [HTTPResponse] = [.error(500), .ok, .ok, .error(404), .error(403)]
	///     let sortedResponses = responses.sorted {
	///         switch ($0, $1) {
	///         // Order errors by code
	///         case let (.error(aCode), .error(bCode)):
	///             return aCode < bCode
	///
	///         // All successes are equivalent, so none is before any other
	///         case (.ok, .ok): return false
	///
	///         // Order errors before successes
	///         case (.error, .ok): return true
	///         case (.ok, .error): return false
	///         }
	///     }
	///     print(sortedResponses)
	///     // Prints "[.error(403), .error(404), .error(500), .ok, .ok]"
	///
	/// You also use this method to sort elements that conform to the
	/// `Comparable` protocol in descending order. To sort your collection
	/// in descending order, pass the greater-than operator (`>`) as the
	/// `areInIncreasingOrder` parameter.
	///
	///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
	///     let descendingStudents = students.sorted(by: >)
	///     print(descendingStudents)
	///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
	///
	/// Calling the related `sorted()` method is equivalent to calling this
	/// method and passing the less-than operator (`<`) as the predicate.
	///
	///     print(students.sorted())
	///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
	///     print(students.sorted(by: <))
	///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
	///
	/// - Parameter areInIncreasingOrder: A predicate that returns `true` if its first
	///   argument should be ordered before its second argument; otherwise,
	///   `false`.
	/// - Returns: A sorted array of the collection's elements.
	///
	/// - SeeAlso: `sorted()`
	/// - MutatingVariant: sort
	public func sorted(by areInIncreasingOrder: (Element, Element) -> Bool) -> [Element]
	
	/// Sorts the collection in place, using the given predicate as the
	/// comparison between elements.
	///
	/// When you want to sort a collection of elements that doesn't conform to
	/// the `Comparable` protocol, pass a closure to this method that returns
	/// `true` when the first element passed should be ordered before the
	/// second.
	///
	/// The predicate must be a *strict weak ordering* over the elements. That
	/// is, for any elements `a`, `b`, and `c`, the following conditions must
	/// hold:
	///
	/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
	/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
	///   both `true`, then `areInIncreasingOrder(a, c)` is also `true`.
	///   (Transitive comparability)
	/// - Two elements are *incomparable* if neither is ordered before the other
	///   according to the predicate. If `a` and `b` are incomparable, and `b`
	///   and `c` are incomparable, then `a` and `c` are also incomparable.
	///   (Transitive incomparability)
	///
	/// The sorting algorithm is not stable. A nonstable sort may change the
	/// relative order of elements for which `areInIncreasingOrder` does not
	/// establish an order.
	///
	/// In the following example, the closure provides an ordering for an array
	/// of a custom enumeration that describes an HTTP response. The predicate
	/// orders errors before successes and sorts the error responses by their
	/// error code.
	///
	///     enum HTTPResponse {
	///         case ok
	///         case error(Int)
	///     }
	///
	///     var responses: [HTTPResponse] = [.error(500), .ok, .ok, .error(404), .error(403)]
	///     responses.sort {
	///         switch ($0, $1) {
	///         // Order errors by code
	///         case let (.error(aCode), .error(bCode)):
	///             return aCode < bCode
	///
	///         // All successes are equivalent, so none is before any other
	///         case (.ok, .ok): return false
	///
	///         // Order errors before successes
	///         case (.error, .ok): return true
	///         case (.ok, .error): return false
	///         }
	///     }
	///     print(responses)
	///     // Prints "[.error(403), .error(404), .error(500), .ok, .ok]"
	///
	/// Alternatively, use this method to sort a collection of elements that do
	/// conform to `Comparable` when you want the sort to be descending instead
	/// of ascending. Pass the greater-than operator (`>`) operator as the
	/// predicate.
	///
	///     var students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
	///     students.sort(by: >)
	///     print(students)
	///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
	///
	/// - Parameter areInIncreasingOrder: A predicate that returns `true` if its first
	///   argument should be ordered before its second argument; otherwise,
	///   `false`.
	public mutating func sort(by areInIncreasingOrder: (Element, Element) -> Bool)
	
	/// Accesses a contiguous subrange of the collection's elements.
	///
	/// The accessed slice uses the same indices for the same elements as the
	/// original collection. Always use the slice's `startIndex` property
	/// instead of assuming that its indices start at a particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let index = streetsSlice.index(of: "Evarts")    // 4
	///     print(streets[index!])
	///     // Prints "Evarts"
	///
	/// - Parameter bounds: A range of the collection's indices. The bounds of
	///   the range must be valid indices of the collection.
	public subscript(bounds: ClosedRange<Int>) -> ArraySlice<Element> { get }
	
	/// Accesses a contiguous subrange of the collection's elements.
	///
	/// The accessed slice uses the same indices for the same elements as the
	/// original collection. Always use the slice's `startIndex` property
	/// instead of assuming that its indices start at a particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let index = streetsSlice.index(of: "Evarts")    // 4
	///     print(streets[index!])
	///     // Prints "Evarts"
	///
	/// - Parameter bounds: A range of the collection's indices. The bounds of
	///   the range must be valid indices of the collection.
	public subscript(bounds: CountableRange<Int>) -> ArraySlice<Element> { get }
	
	/// Accesses a contiguous subrange of the collection's elements.
	///
	/// The accessed slice uses the same indices for the same elements as the
	/// original collection. Always use the slice's `startIndex` property
	/// instead of assuming that its indices start at a particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let index = streetsSlice.index(of: "Evarts")    // 4
	///     print(streets[index!])
	///     // Prints "Evarts"
	///
	/// - Parameter bounds: A range of the collection's indices. The bounds of
	///   the range must be valid indices of the collection.
	public subscript(bounds: CountableClosedRange<Int>) -> ArraySlice<Element> { get }
	
	/// Accesses a contiguous subrange of the collection's elements.
	///
	/// The accessed slice uses the same indices for the same elements as the
	/// original collection. Always use the slice's `startIndex` property
	/// instead of assuming that its indices start at a particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let index = streetsSlice.index(of: "Evarts")    // 4
	///     streets[index!] = "Eustace"
	///     print(streets[index!])
	///     // Prints "Eustace"
	///
	/// - Parameter bounds: A range of the collection's indices. The bounds of
	///   the range must be valid indices of the collection.
	public subscript(bounds: ClosedRange<Int>) -> ArraySlice<Element>
	
	/// Accesses a contiguous subrange of the collection's elements.
	///
	/// The accessed slice uses the same indices for the same elements as the
	/// original collection. Always use the slice's `startIndex` property
	/// instead of assuming that its indices start at a particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let index = streetsSlice.index(of: "Evarts")    // 4
	///     streets[index!] = "Eustace"
	///     print(streets[index!])
	///     // Prints "Eustace"
	///
	/// - Parameter bounds: A range of the collection's indices. The bounds of
	///   the range must be valid indices of the collection.
	public subscript(bounds: CountableRange<Int>) -> ArraySlice<Element>
	
	/// Accesses a contiguous subrange of the collection's elements.
	///
	/// The accessed slice uses the same indices for the same elements as the
	/// original collection. Always use the slice's `startIndex` property
	/// instead of assuming that its indices start at a particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let index = streetsSlice.index(of: "Evarts")    // 4
	///     streets[index!] = "Eustace"
	///     print(streets[index!])
	///     // Prints "Eustace"
	///
	/// - Parameter bounds: A range of the collection's indices. The bounds of
	///   the range must be valid indices of the collection.
	public subscript(bounds: CountableClosedRange<Int>) -> ArraySlice<Element>
	
	/// A sequence containing the same elements as this sequence,
	/// but on which some operations, such as `map` and `filter`, are
	/// implemented lazily.
	///
	/// - SeeAlso: `LazySequenceProtocol`, `LazySequence`
	public var lazy: LazySequence<ContiguousArray<Element>> { get }
	
	/// Accesses a contiguous subrange of the collection's elements.
	///
	/// The accessed slice uses the same indices for the same elements as the
	/// original collection. Always use the slice's `startIndex` property
	/// instead of assuming that its indices start at a particular value.
	///
	/// This example demonstrates getting a slice of an array of strings, finding
	/// the index of one of the strings in the slice, and then using that index
	/// in the original array.
	///
	///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
	///     let streetsSlice = streets[2 ..< streets.endIndex]
	///     print(streetsSlice)
	///     // Prints "["Channing", "Douglas", "Evarts"]"
	///
	///     let index = streetsSlice.index(of: "Evarts")    // 4
	///     streets[index!] = "Eustace"
	///     print(streets[index!])
	///     // Prints "Eustace"
	///
	/// - Parameter bounds: A range of the collection's indices. The bounds of
	///   the range must be valid indices of the collection.
	public subscript(bounds: Range<Int>) -> MutableSlice<ContiguousArray<Element>>
	
	/// The indices that are valid for subscripting the collection, in ascending
	/// order.
	///
	/// A collection's `indices` property can hold a strong reference to the
	/// collection itself, causing the collection to be non-uniquely referenced.
	/// If you mutate the collection while iterating over its indices, a strong
	/// reference can cause an unexpected copy of the collection. To avoid the
	/// unexpected copy, use the `index(after:)` method starting with
	/// `startIndex` to produce indices instead.
	///
	///     var c = MyFancyCollection([10, 20, 30, 40, 50])
	///     var i = c.startIndex
	///     while i != c.endIndex {
	///         c[i] /= 5
	///         i = c.index(after: i)
	///     }
	///     // c == MyFancyCollection([2, 4, 6, 8, 10])
	public var indices: CountableRange<Int> { get }
	
	/// Returns a view presenting the elements of the collection in reverse
	/// order.
	///
	/// You can reverse a collection without allocating new space for its
	/// elements by calling this `reversed()` method. A
	/// `ReversedRandomAccessCollection` instance wraps an underlying collection
	/// and provides access to its elements in reverse order. This example
	/// prints the elements of an array in reverse order:
	///
	///     let numbers = [3, 5, 7]
	///     for number in numbers.reversed() {
	///         print(number)
	///     }
	///     // Prints "7"
	///     // Prints "5"
	///     // Prints "3"
	///
	/// If you need a reversed collection of the same type, you may be able to
	/// use the collection's sequence-based or collection-based initializer. For
	/// example, to get the reversed version of an array, initialize a new
	/// `Array` instance from the result of this `reversed()` method.
	///
	///     let reversedNumbers = Array(numbers.reversed())
	///     print(reversedNumbers)
	///     // Prints "[7, 5, 3]"
	///
	/// - Complexity: O(1)
	public func reversed() -> ReversedRandomAccessCollection<ContiguousArray<Element>>
	
	/// Returns an array containing the results of mapping the given closure
	/// over the sequence's elements.
	///
	/// In this example, `map` is used first to convert the names in the array
	/// to lowercase strings and then to count their characters.
	///
	///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
	///     let lowercaseNames = cast.map { $0.lowercaseString }
	///     // 'lowercaseNames' == ["vivien", "marlon", "kim", "karl"]
	///     let letterCounts = cast.map { $0.characters.count }
	///     // 'letterCounts' == [6, 6, 3, 4]
	///
	/// - Parameter transform: A mapping closure. `transform` accepts an
	///   element of this sequence as its parameter and returns a transformed
	///   value of the same or of a different type.
	/// - Returns: An array containing the transformed elements of this
	///   sequence.
	public func map<T>(_ transform: (Element) throws -> T) rethrows -> [T]
	
	/// Returns an array containing, in order, the elements of the sequence
	/// that satisfy the given predicate.
	///
	/// In this example, `filter` is used to include only names shorter than
	/// five characters.
	///
	///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
	///     let shortNames = cast.filter { $0.characters.count < 5 }
	///     print(shortNames)
	///     // Prints "["Kim", "Karl"]"
	///
	/// - Parameter shouldInclude: A closure that takes an element of the
	///   sequence as its argument and returns a Boolean value indicating
	///   whether the element should be included in the returned array.
	/// - Returns: An array of the elements that `includeElement` allowed.
	public func filter(_ isIncluded: (Element) throws -> Bool) rethrows -> [Element]
	
	/// Returns a value less than or equal to the number of elements in
	/// the sequence, nondestructively.
	///
	/// - Complexity: O(*n*)
	public var underestimatedCount: Int { get }
	
	/// Calls the given closure on each element in the sequence in the same order
	/// as a `for`-`in` loop.
	///
	/// The two loops in the following example produce the same output:
	///
	///     let numberWords = ["one", "two", "three"]
	///     for word in numberWords {
	///         print(word)
	///     }
	///     // Prints "one"
	///     // Prints "two"
	///     // Prints "three"
	///
	///     numberWords.forEach { word in
	///         print(word)
	///     }
	///     // Same as above
	///
	/// Using the `forEach` method is distinct from a `for`-`in` loop in two
	/// important ways:
	///
	/// 1. You cannot use a `break` or `continue` statement to exit the current
	///    call of the `body` closure or skip subsequent calls.
	/// 2. Using the `return` statement in the `body` closure will exit only from
	///    the current call to `body`, not from any outer scope, and won't skip
	///    subsequent calls.
	///
	/// - Parameter body: A closure that takes an element of the sequence as a
	///   parameter.
	public func forEach(_ body: (Element) throws -> Void) rethrows
	
	/// Returns the first element of the sequence that satisfies the given
	/// predicate or nil if no such element is found.
	///
	/// - Parameter predicate: A closure that takes an element of the
	///   sequence as its argument and returns a Boolean value indicating
	///   whether the element is a match.
	/// - Returns: The first match or `nil` if there was no match.
	public func first(where predicate: (Element) throws -> Bool) rethrows -> Element?
	
	/// Returns a subsequence containing all but the first element of the
	/// sequence.
	///
	/// The following example drops the first element from an array of integers.
	///
	///     let numbers = [1, 2, 3, 4, 5]
	///     print(numbers.dropFirst())
	///     // Prints "[2, 3, 4, 5]"
	///
	/// If the sequence has no elements, the result is an empty subsequence.
	///
	///     let empty: [Int] = []
	///     print(empty.dropFirst())
	///     // Prints "[]"
	///
	/// - Returns: A subsequence starting after the first element of the
	///   sequence.
	///
	/// - Complexity: O(1)
	public func dropFirst() -> ArraySlice<Element>
	
	/// Returns a subsequence containing all but the last element of the
	/// sequence.
	///
	/// The sequence must be finite. If the sequence has no elements, the result
	/// is an empty subsequence.
	///
	///     let numbers = [1, 2, 3, 4, 5]
	///     print(numbers.dropLast())
	///     // Prints "[1, 2, 3, 4]"
	///
	/// If the sequence has no elements, the result is an empty subsequence.
	///
	///     let empty: [Int] = []
	///     print(empty.dropLast())
	///     // Prints "[]"
	///
	/// - Returns: A subsequence leaving off the last element of the sequence.
	///
	/// - Complexity: O(*n*), where *n* is the length of the sequence.
	public func dropLast() -> ArraySlice<Element>
	
	/// Returns a sequence of pairs (*n*, *x*), where *n* represents a
	/// consecutive integer starting at zero, and *x* represents an element of
	/// the sequence.
	///
	/// This example enumerates the characters of the string "Swift" and prints
	/// each character along with its place in the string.
	///
	///     for (n, c) in "Swift".characters.enumerated() {
	///         print("\(n): '\(c)'")
	///     }
	///     // Prints "0: 'S'"
	///     // Prints "1: 'w'"
	///     // Prints "2: 'i'"
	///     // Prints "3: 'f'"
	///     // Prints "4: 't'"
	///
	/// When enumerating a collection, the integer part of each pair is a counter
	/// for the enumeration, not necessarily the index of the paired value.
	/// These counters can only be used as indices in instances of zero-based,
	/// integer-indexed collections, such as `Array` and `ContiguousArray`. For
	/// other collections the counters may be out of range or of the wrong type
	/// to use as an index. To iterate over the elements of a collection with its
	/// indices, use the `zip(_:_:)` function.
	///
	/// This example iterates over the indices and elements of a set, building a
	/// list of indices of names with five or fewer letters.
	///
	///     let names: Set = ["Sofia", "Camilla", "Martina", "Mateo", "Nicolás"]
	///     var shorterIndices: [SetIndex<String>] = []
	///     for (i, name) in zip(names.indices, names) {
	///         if name.characters.count <= 5 {
	///             shorterIndices.append(i)
	///         }
	///     }
	///
	/// Now that the `shorterIndices` array holds the indices of the shorter
	/// names in the `names` set, you can use those indices to access elements in
	/// the set.
	///
	///     for i in shorterIndices {
	///         print(names[i])
	///     }
	///     // Prints "Sofia"
	///     // Prints "Mateo"
	///
	/// - Returns: A sequence of pairs enumerating the sequence.
	public func enumerated() -> EnumeratedSequence<ContiguousArray<Element>>
	
	/// Returns the minimum element in the sequence, using the given predicate as
	/// the comparison between elements.
	///
	/// The predicate must be a *strict weak ordering* over the elements. That
	/// is, for any elements `a`, `b`, and `c`, the following conditions must
	/// hold:
	///
	/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
	/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
	///   both `true`, then `areInIncreasingOrder(a, c)` is also
	///   `true`. (Transitive comparability)
	/// - Two elements are *incomparable* if neither is ordered before the other
	///   according to the predicate. If `a` and `b` are incomparable, and `b`
	///   and `c` are incomparable, then `a` and `c` are also incomparable.
	///   (Transitive incomparability)
	///
	/// This example shows how to use the `min(by:)` method on a
	/// dictionary to find the key-value pair with the lowest value.
	///
	///     let hues = ["Heliotrope": 296, "Coral": 16, "Aquamarine": 156]
	///     let leastHue = hues.min { a, b in a.value < b.value }
	///     print(leastHue)
	///     // Prints "Optional(("Coral", 16))"
	///
	/// - Parameter areInIncreasingOrder: A predicate that returns `true`
	///   if its first argument should be ordered before its second
	///   argument; otherwise, `false`.
	/// - Returns: The sequence's minimum element, according to
	///   `areInIncreasingOrder`. If the sequence has no elements, returns
	///   `nil`.
	///
	/// - SeeAlso: `min()`
	@warn_unqualified_access
	public func min(by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Element?
	
	/// Returns the maximum element in the sequence, using the given predicate
	/// as the comparison between elements.
	///
	/// The predicate must be a *strict weak ordering* over the elements. That
	/// is, for any elements `a`, `b`, and `c`, the following conditions must
	/// hold:
	///
	/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
	/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
	///   both `true`, then `areInIncreasingOrder(a, c)` is also
	///   `true`. (Transitive comparability)
	/// - Two elements are *incomparable* if neither is ordered before the other
	///   according to the predicate. If `a` and `b` are incomparable, and `b`
	///   and `c` are incomparable, then `a` and `c` are also incomparable.
	///   (Transitive incomparability)
	///
	/// This example shows how to use the `max(by:)` method on a
	/// dictionary to find the key-value pair with the highest value.
	///
	///     let hues = ["Heliotrope": 296, "Coral": 16, "Aquamarine": 156]
	///     let greatestHue = hues.max { a, b in a.value < b.value }
	///     print(greatestHue)
	///     // Prints "Optional(("Heliotrope", 296))"
	///
	/// - Parameter areInIncreasingOrder:  A predicate that returns `true` if its
	///   first argument should be ordered before its second argument;
	///   otherwise, `false`.
	/// - Returns: The sequence's maximum element if the sequence is not empty;
	///   otherwise, `nil`.
	///
	/// - SeeAlso: `max()`
	@warn_unqualified_access
	public func max(by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Element?
	
	/// Returns a Boolean value indicating whether the initial elements of the
	/// sequence are equivalent to the elements in another sequence, using
	/// the given predicate as the equivalence test.
	///
	/// The predicate must be a *equivalence relation* over the elements. That
	/// is, for any elements `a`, `b`, and `c`, the following conditions must
	/// hold:
	///
	/// - `areEquivalent(a, a)` is always `true`. (Reflexivity)
	/// - `areEquivalent(a, b)` implies `areEquivalent(b, a)`. (Symmetry)
	/// - If `areEquivalent(a, b)` and `areEquivalent(b, c)` are both `true`, then
	///   `areEquivalent(a, c)` is also `true`. (Transitivity)
	///
	/// - Parameters:
	///   - possiblePrefix: A sequence to compare to this sequence.
	///   - areEquivalent: A predicate that returns `true` if its two arguments
	///     are equivalent; otherwise, `false`.
	/// - Returns: `true` if the initial elements of the sequence are equivalent
	///   to the elements of `possiblePrefix`; otherwise, `false`. If
	///   `possiblePrefix` has no elements, the return value is `true`.
	///
	/// - SeeAlso: `starts(with:)`
	public func starts<PossiblePrefix where PossiblePrefix : Sequence, PossiblePrefix.Iterator.Element == Element>(with possiblePrefix: PossiblePrefix, by areEquivalent: (Element, Element) throws -> Bool) rethrows -> Bool
	
	/// Returns a Boolean value indicating whether this sequence and another
	/// sequence contain equivalent elements, using the given predicate as the
	/// equivalence test.
	///
	/// At least one of the sequences must be finite.
	///
	/// The predicate must be a *equivalence relation* over the elements. That
	/// is, for any elements `a`, `b`, and `c`, the following conditions must
	/// hold:
	///
	/// - `areEquivalent(a, a)` is always `true`. (Reflexivity)
	/// - `areEquivalent(a, b)` implies `areEquivalent(b, a)`. (Symmetry)
	/// - If `areEquivalent(a, b)` and `areEquivalent(b, c)` are both `true`, then
	///   `areEquivalent(a, c)` is also `true`. (Transitivity)
	///
	/// - Parameters:
	///   - other: A sequence to compare to this sequence.
	///   - areEquivalent: A predicate that returns `true` if its two arguments
	///     are equivalent; otherwise, `false`.
	/// - Returns: `true` if this sequence and `other` contain equivalent items,
	///   using `areEquivalent` as the equivalence test; otherwise, `false.`
	///
	/// - SeeAlso: `elementsEqual(_:)`
	public func elementsEqual<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence, by areEquivalent: (Element, Element) throws -> Bool) rethrows -> Bool
	
	/// Returns a Boolean value indicating whether the sequence precedes another
	/// sequence in a lexicographical (dictionary) ordering, using the given
	/// predicate to compare elements.
	///
	/// The predicate must be a *strict weak ordering* over the elements. That
	/// is, for any elements `a`, `b`, and `c`, the following conditions must
	/// hold:
	///
	/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
	/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
	///   both `true`, then `areInIncreasingOrder(a, c)` is also
	///   `true`. (Transitive comparability)
	/// - Two elements are *incomparable* if neither is ordered before the other
	///   according to the predicate. If `a` and `b` are incomparable, and `b`
	///   and `c` are incomparable, then `a` and `c` are also incomparable.
	///   (Transitive incomparability)
	///
	/// - Parameters:
	///   - other: A sequence to compare to this sequence.
	///   - areInIncreasingOrder:  A predicate that returns `true` if its first
	///     argument should be ordered before its second argument; otherwise,
	///     `false`.
	/// - Returns: `true` if this sequence precedes `other` in a dictionary
	///   ordering as ordered by `areInIncreasingOrder`; otherwise, `false`.
	///
	/// - Note: This method implements the mathematical notion of lexicographical
	///   ordering, which has no connection to Unicode.  If you are sorting
	///   strings to present to the end user, use `String` APIs that perform
	///   localized comparison instead.
	/// - SeeAlso: `lexicographicallyPrecedes(_:)`
	public func lexicographicallyPrecedes<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence, by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Bool
	
	/// Returns a Boolean value indicating whether the sequence contains an
	/// element that satisfies the given predicate.
	///
	/// You can use the predicate to check for an element of a type that
	/// doesn't conform to the `Equatable` protocol, such as the
	/// `HTTPResponse` enumeration in this example.
	///
	///     enum HTTPResponse {
	///         case ok
	///         case error(Int)
	///     }
	///
	///     let lastThreeResponses: [HTTPResponse] = [.ok, .ok, .error(404)]
	///     let hadError = lastThreeResponses.contains { element in
	///         if case .error = element {
	///             return true
	///         } else {
	///             return false
	///         }
	///     }
	///     // 'hadError' == true
	///
	/// Alternatively, a predicate can be satisfied by a range of `Equatable`
	/// elements or a general condition. This example shows how you can check an
	/// array for an expense greater than $100.
	///
	///     let expenses = [21.37, 55.21, 9.32, 10.18, 388.77, 11.41]
	///     let hasBigPurchase = expenses.contains { $0 > 100 }
	///     // 'hasBigPurchase' == true
	///
	/// - Parameter predicate: A closure that takes an element of the sequence
	///   as its argument and returns a Boolean value that indicates whether
	///   the passed element represents a match.
	/// - Returns: `true` if the sequence contains an element that satisfies
	///   `predicate`; otherwise, `false`.
	public func contains(where predicate: (Element) throws -> Bool) rethrows -> Bool
	
	/// Returns the result of calling the given combining closure with each
	/// element of this sequence and an accumulating value.
	///
	/// The `nextPartialResult` closure is called sequentially with an
	/// accumulating value initialized to `initialResult` and each
	/// element of the sequence. This example shows how to find the sum
	/// of an array of numbers.
	///
	///     let numbers = [1, 2, 3, 4]
	///     let addTwo: (Int, Int) -> Int = { x, y in x + y }
	///     let numberSum = numbers.reduce(0, addTwo)
	///     // 'numberSum' == 10
	///
	/// When `numbers.reduce(_:_:)` is called, the
	/// following steps occur:
	///
	/// 1. The `nextPartialResult` closure is called with the initial
	///    result and the first element of `numbers`, returning the sum:
	///    `1`.
	/// 2. The closure is called again repeatedly with the previous call's
	///    return value and each element of the sequence.
	/// 3. When the sequence is exhausted, the last value returned from the
	///    closure is returned to the caller.
	///
	/// - Parameters:
	///   - initialResult: the initial accumulating value.
	///   - nextPartialResult: A closure that combines an accumulating
	///     value and an element of the sequence into a new accumulating
	///     value, to be used in the next call of the
	///     `nextPartialResult` closure or returned to the caller.
	/// - Returns: The final accumulated value.
	public func reduce<Result>(_ initialResult: Result, _ nextPartialResult: (Result, Element) throws -> Result) rethrows -> Result
	
	/// Returns an array containing the concatenated results of calling the
	/// given transformation with each element of this sequence.
	///
	/// Use this method to receive a single-level collection when your
	/// transformation produces a sequence or collection for each element.
	///
	/// In this example, note the difference in the result of using `map` and
	/// `flatMap` with a transformation that returns an array.
	///
	///     let numbers = [1, 2, 3, 4]
	///
	///     let mapped = numbers.map { Array(count: $0, repeatedValue: $0) }
	///     // [[1], [2, 2], [3, 3, 3], [4, 4, 4, 4]]
	///
	///     let flatMapped = numbers.flatMap { Array(count: $0, repeatedValue: $0) }
	///     // [1, 2, 2, 3, 3, 3, 4, 4, 4, 4]
	///
	/// In fact, `s.flatMap(transform)`  is equivalent to
	/// `Array(s.map(transform).joined())`.
	///
	/// - Parameter transform: A closure that accepts an element of this
	///   sequence as its argument and returns a sequence or collection.
	/// - Returns: The resulting flattened array.
	///
	/// - Complexity: O(*m* + *n*), where *m* is the length of this sequence
	///   and *n* is the length of the result.
	/// - SeeAlso: `joined()`, `map(_:)`
	public func flatMap<SegmentOfResult : Sequence>(_ transform: (Element) throws -> SegmentOfResult) rethrows -> [SegmentOfResult.Iterator.Element]
	
	/// Returns an array containing the non-`nil` results of calling the given
	/// transformation with each element of this sequence.
	///
	/// Use this method to receive an array of nonoptional values when your
	/// transformation produces an optional value.
	///
	/// In this example, note the difference in the result of using `map` and
	/// `flatMap` with a transformation that returns an optional `Int` value.
	///
	///     let possibleNumbers = ["1", "2", "three", "///4///", "5"]
	///
	///     let mapped: [Int?] = numbers.map { str in Int(str) }
	///     // [1, 2, nil, nil, 5]
	///
	///     let flatMapped: [Int] = numbers.flatMap { str in Int(str) }
	///     // [1, 2, 5]
	///
	/// - Parameter transform: A closure that accepts an element of this
	///   sequence as its argument and returns an optional value.
	/// - Returns: An array of the non-`nil` results of calling `transform`
	///   with each element of the sequence.
	///
	/// - Complexity: O(*m* + *n*), where *m* is the length of this sequence
	///   and *n* is the length of the result.
	public func flatMap<ElementOfResult>(_ transform: (Element) throws -> ElementOfResult?) rethrows -> [ElementOfResult]
	}
	
	/// Supply the default `makeIterator()` method for `Collection` models
	/// that accept the default associated `Iterator`,
	/// `IndexingIterator<Self>`.
	extension ContiguousArray {
		
		/// Returns an iterator over the elements of the collection.
		public func makeIterator() -> IndexingIterator<ContiguousArray<Element>>
	}
	
	/// Default implementations of core requirements
	extension ContiguousArray {
		
		/// A Boolean value indicating whether the collection is empty.
		///
		/// When you need to check whether your collection is empty, use the
		/// `isEmpty` property instead of checking that the `count` property is
		/// equal to zero. For collections that don't conform to
		/// `RandomAccessCollection`, accessing the `count` property iterates
		/// through the elements of the collection.
		///
		///     let horseName = "Silver"
		///     if horseName.characters.isEmpty {
		///         print("I've been through the desert on a horse with no name.")
		///     } else {
		///         print("Hi ho, \(horseName)!")
		///     }
		///     // Prints "Hi ho, Silver!")
		///
		/// - Complexity: O(1)
		public var isEmpty: Bool { get }
		
		/// The first element of the collection.
		///
		/// If the collection is empty, the value of this property is `nil`.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     if let firstNumber = numbers.first {
		///         print(firstNumber)
		///     }
		///     // Prints "10"
		public var first: Element? { get }
		
		/// A value less than or equal to the number of elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the length
		///   of the collection.
		public var underestimatedCount: Int { get }
		
		/// The number of elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the length
		///   of the collection.
		public var count: Int { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension ContiguousArray {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyBidirectionalCollection<ContiguousArray<Element>> { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension ContiguousArray {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyCollection<ContiguousArray<Element>> { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension ContiguousArray {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyRandomAccessCollection<ContiguousArray<Element>> { get }
	}
	
	/// Default implementation for forward collections.
	extension ContiguousArray {
		
		/// Offsets the given index by the specified distance.
		///
		/// The value passed as `n` must not offset `i` beyond the `endIndex` or
		/// before the `startIndex` of this collection.
		///
		/// - Parameters:
		///   - i: A valid index of the collection.
		///   - n: The distance to offset `i`. `n` must not be negative unless the
		///     collection conforms to the `BidirectionalCollection` protocol.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the absolute
		///   value of `n`.
		public func formIndex(_ i: inout Int, offsetBy n: Int)
		
		/// Offsets the given index by the specified distance, or so that it equals
		/// the given limiting index.
		///
		/// The value passed as `n` must not offset `i` beyond the `endIndex` or
		/// before the `startIndex` of this collection, unless the index passed as
		/// `limit` prevents offsetting beyond those bounds.
		///
		/// - Parameters:
		///   - i: A valid index of the collection.
		///   - n: The distance to offset `i`. `n` must not be negative unless the
		///     collection conforms to the `BidirectionalCollection` protocol.
		/// - Returns: `true` if `i` has been offset by exactly `n` steps without
		///   going beyond `limit`; otherwise, `false`. When the return value is
		///   `false`, the value of `i` is equal to `limit`.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the absolute
		///   value of `n`.
		public func formIndex(_ i: inout Int, offsetBy n: Int, limitedBy limit: Int) -> Bool
	}
	
	extension ContiguousArray : CustomReflectable {
		
		/// A mirror that reflects the array.
		public var customMirror: Mirror { get }
	}
	
	extension ContiguousArray : RangeReplaceableCollection {
		
		/// Creates a new, empty array.
		///
		/// This is equivalent to initializing with an empty array literal.
		/// For example:
		///
		///     var emptyArray = Array<Int>()
		///     print(emptyArray.isEmpty)
		///     // Prints "true"
		///
		///     emptyArray = []
		///     print(emptyArray.isEmpty)
		///     // Prints "true"
		public init()
		
		/// Creates an array containing the elements of a sequence.
		///
		/// You can use this initializer to create an array from any other type that
		/// conforms to the `Sequence` protocol. For example, you might want to
		/// create an array with the integers from 1 through 7. Use this initializer
		/// around a range instead of typing all those numbers in an array literal.
		///
		///     let numbers = Array(1...7)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 6, 7]"
		///
		/// You can also use this initializer to convert a complex sequence or
		/// collection type back to an array. For example, the `keys` property of
		/// a dictionary isn't an array with its own storage, it's a collection
		/// that maps its elements from the dictionary only when they're
		/// accessed, saving the time and space needed to allocate an array. If
		/// you need to pass those keys to a method that takes an array, however,
		/// use this initializer to convert that list from its type of
		/// `LazyMapCollection<Dictionary<String, Int>, Int>` to a simple
		/// `[String]`.
		///
		///     func cacheImagesWithNames(names: [String]) {
		///         // custom image loading and caching
		///      }
		///
		///     let namedHues: [String: Int] = ["Vermillion": 18, "Magenta": 302,
		///             "Gold": 50, "Cerise": 320]
		///     let colorNames = Array(namedHues.keys)
		///     cacheImagesWithNames(colorNames)
		///
		///     print(colorNames)
		///     // Prints "["Gold", "Cerise", "Magenta", "Vermillion"]"
		///
		/// - Parameter s: The sequence of elements to turn into an array.
		public init<S : Sequence where S.Iterator.Element == Element>(_ s: S)
		
		/// Creates a new array containing the specified number of a single, repeated
		/// value.
		///
		/// Here's an example of creating an array initialized with five strings
		/// containing the letter *Z*.
		///
		///     let fiveZs = Array(repeating: "Z", count: 5)
		///     print(fiveZs)
		///     // Prints "["Z", "Z", "Z", "Z", "Z"]"
		///
		/// - Parameters:
		///   - repeatedValue: The element to repeat.
		///   - count: The number of times to repeat the value passed in the
		///     `repeating` parameter. `count` must be zero or greater.
		public init(repeating repeatedValue: Element, count: Int)
		
		/// The number of elements in the array.
		public var count: Int { get }
		
		/// The total number of elements that the array can contain using its current
		/// storage.
		///
		/// If the array grows larger than its capacity, it discards its current
		/// storage and allocates a larger one.
		///
		/// The following example creates an array of integers from an array literal,
		/// then appends the elements of another collection. Before appending, the
		/// array allocates new storage that is large enough store the resulting
		/// elements.
		///
		///     var numbers = [10, 20, 30, 40, 50]
		///     print("Count: \(numbers.count), capacity: \(numbers.capacity)")
		///     // Prints "Count: 5, capacity: 5"
		///
		///     numbers.append(contentsOf: stride(from: 60, through: 100, by: 10))
		///     print("Count: \(numbers.count), capacity: \(numbers.capacity)")
		///     // Prints "Count: 10, capacity: 12"
		public var capacity: Int { get }
		
		/// Reserves enough space to store the specified number of elements.
		///
		/// If you are adding a known number of elements to an array, use this method
		/// to avoid multiple reallocations. This method ensures that the array has
		/// unique, mutable, contiguous storage, with space allocated for at least
		/// the requested number of elements.
		///
		/// For performance reasons, the newly allocated storage may be larger than
		/// the requested capacity. Use the array's `capacity` property to determine
		/// the size of the new storage.
		///
		/// - Parameter minimumCapacity: The requested number of elements to store.
		///
		/// - Complexity: O(*n*), where *n* is the count of the array.
		public mutating func reserveCapacity(_ minimumCapacity: Int)
		
		/// Adds a new element at the end of the array.
		///
		/// Use this method to append a single element to the end of a mutable array.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(100)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 100]"
		///
		/// Because arrays increase their allocated capacity using an exponential
		/// strategy, appending a single element to an array is an O(1) operation
		/// when averaged over many calls to the `append(_:)` method. When an array
		/// has additional capacity and is not sharing its storage with another
		/// instance, appending an element is O(1). When an array needs to
		/// reallocate storage before appending or its storage is shared with
		/// another copy, appending is O(*n*), where *n* is the length of the array.
		///
		/// - Parameter newElement: The element to append to the array.
		///
		/// - Complexity: Amortized O(1) over many additions. If the array uses a
		///   bridged `NSArray` instance as its storage, the efficiency is
		///   unspecified.
		public mutating func append(_ newElement: Element)
		
		/// Adds the elements of a sequence to the end of the array.
		///
		/// Use this method to append the elements of a sequence to the end of an
		/// array. This example appends the elements of a `Range<Int>` instance
		/// to an array of integers.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(contentsOf: 10...15)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
		///
		/// - Parameter newElements: The elements to append to the array.
		///
		/// - Complexity: O(*n*), where *n* is the length of the resulting array.
		public mutating func append<S : Sequence where S.Iterator.Element == Element>(contentsOf newElements: S)
		
		/// Adds the elements of a collection to the end of the array.
		///
		/// Use this method to append the elements of a collection to the end of this
		/// array. This example appends the elements of a `Range<Int>` instance
		/// to an array of integers.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(contentsOf: 10...15)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
		///
		/// - Parameter newElements: The elements to append to the array.
		///
		/// - Complexity: O(*n*), where *n* is the length of the resulting array.
		public mutating func append<C : Collection where C.Iterator.Element == Element>(contentsOf newElements: C)
		
		/// Inserts a new element at the specified position.
		///
		/// The new element is inserted before the element currently at the specified
		/// index. If you pass the array's `endIndex` property as the `index`
		/// parameter, the new element is appended to the array.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.insert(100, at: 3)
		///     numbers.insert(200, at: numbers.endIndex)
		///
		///     print(numbers)
		///     // Prints "[1, 2, 3, 100, 4, 5, 200]"
		///
		/// - Parameter newElement: The new element to insert into the array.
		/// - Parameter i: The position at which to insert the new element.
		///   `index` must be a valid index of the array or equal to its `endIndex`
		///   property.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func insert(_ newElement: Element, at i: Int)
		
		/// Removes and returns the element at the specified position.
		///
		/// All the elements following the specified position are moved up to
		/// close the gap.
		///
		///     var measurements: [Double] = [1.1, 1.5, 2.9, 1.2, 1.5, 1.3, 1.2]
		///     let removed = measurements.remove(at: 2)
		///     print(measurements)
		///     // Prints "[1.1, 1.5, 1.2, 1.5, 1.3, 1.2]"
		///
		/// - Parameter index: The position of the element to remove. `index` must
		///   be a valid index of the array.
		/// - Returns: The element at the specified index.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func remove(at index: Int) -> Element
		
		/// Removes all elements from the array.
		///
		/// - Parameter keepCapacity: Pass `true` to keep the existing capacity of
		///   the array after removing its elements. The default value is
		///   `false`.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func removeAll(keepingCapacity keepCapacity: Bool = default)
	}
	
	extension ContiguousArray : ExpressibleByArrayLiteral {
		
		/// Creates an array from the given array literal.
		///
		/// Do not call this initializer directly. It is used by the compiler when
		/// you use an array literal. Instead, create a new array by using an array
		/// literal as its value. To do this, enclose a comma-separated list of
		/// values in square brackets.
		///
		/// Here, an array of strings is created from an array literal holding only
		/// strings:
		///
		///     let ingredients: ContiguousArray =
		///           ["cocoa beans", "sugar", "cocoa butter", "salt"]
		///
		/// - Parameter elements: A variadic list of elements of the new array.
		public init(arrayLiteral elements: Element...)
	}
	
	extension ContiguousArray : CustomStringConvertible, CustomDebugStringConvertible {
		
		/// A textual representation of the array and its elements.
		public var description: String { get }
		
		/// A textual representation of the array and its elements, suitable for
		/// debugging.
		public var debugDescription: String { get }
	}
	
	extension ContiguousArray where Element : Equatable {
		
		/// Returns the longest possible subsequences of the collection, in order,
		/// around elements equal to the given element.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the collection are not returned as part
		/// of any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string at each
		/// space character (" "). The first use of `split` returns each word that
		/// was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(separator: " ")
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(line.characters.split(separator: " ", maxSplits: 1)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(separator: " ", omittingEmptySubsequences: false)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - separator: The element that should be split upon.
		///   - maxSplits: The maximum number of times to split the collection, or
		///     one less than the number of subsequences to return. If
		///     `maxSplits + 1` subsequences are returned, the last one is a suffix
		///     of the original collection containing the remaining elements.
		///     `maxSplits` must be greater than or equal to zero. The default value
		///     is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each consecutive pair of `separator`
		///     elements in the collection and for each instance of `separator` at
		///     the start or end of the collection. If `true`, only nonempty
		///     subsequences are returned. The default value is `true`.
		/// - Returns: An array of subsequences, split from this collection's
		///   elements.
		public func split(separator: Element, maxSplits: Int = default, omittingEmptySubsequences: Bool = default) -> [ArraySlice<Element>]
		
		/// Returns the first index where the specified value appears in the
		/// collection.
		///
		/// After using `index(of:)` to find the position of a particular element in
		/// a collection, you can use it to access the element by subscripting. This
		/// example shows how you can modify one of the names in an array of
		/// students.
		///
		///     var students = ["Ben", "Ivy", "Jordell", "Maxime"]
		///     if let i = students.index(of: "Maxime") {
		///         students[i] = "Max"
		///     }
		///     print(students)
		///     // Prints "["Ben", "Ivy", "Jordell", "Max"]"
		///
		/// - Parameter element: An element to search for in the collection.
		/// - Returns: The first index where `element` is found. If `element` is not
		///   found in the collection, returns `nil`.
		///
		/// - SeeAlso: `index(where:)`
		public func index(of element: Element) -> Int?
		
		/// Returns the longest possible subsequences of the sequence, in order,
		/// around elements equal to the given element.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the sequence are not returned as part of
		/// any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string at each
		/// space character (" "). The first use of `split` returns each word that
		/// was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(separator: " ")
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(line.characters.split(separator: " ", maxSplits: 1)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(separator: " ", omittingEmptySubsequences: false)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - separator: The element that should be split upon.
		///   - maxSplits: The maximum number of times to split the sequence, or one
		///     less than the number of subsequences to return. If `maxSplits + 1`
		///     subsequences are returned, the last one is a suffix of the original
		///     sequence containing the remaining elements. `maxSplits` must be
		///     greater than or equal to zero. The default value is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each consecutive pair of `separator`
		///     elements in the sequence and for each instance of `separator` at the
		///     start or end of the sequence. If `true`, only nonempty subsequences
		///     are returned. The default value is `true`.
		/// - Returns: An array of subsequences, split from this sequence's elements.
		public func split(separator: Element, maxSplits: Int = default, omittingEmptySubsequences: Bool = default) -> [AnySequence<Element>]
		
		/// Returns a Boolean value indicating whether the initial elements of the
		/// sequence are the same as the elements in another sequence.
		///
		/// This example tests whether one countable range begins with the elements
		/// of another countable range.
		///
		///     let a = 1...3
		///     let b = 1...10
		///
		///     print(b.starts(with: a))
		///     // Prints "true"
		///
		/// Passing an sequence with no elements or an empty collection as
		/// `possiblePrefix` always results in `true`.
		///
		///     print(b.starts(with: []))
		///     // Prints "true"
		///
		/// - Parameter possiblePrefix: A sequence to compare to this sequence.
		/// - Returns: `true` if the initial elements of the sequence are the same as
		///   the elements of `possiblePrefix`; otherwise, `false`. If
		///   `possiblePrefix` has no elements, the return value is `true`.
		///
		/// - SeeAlso: `starts(with:by:)`
		public func starts<PossiblePrefix where PossiblePrefix : Sequence, PossiblePrefix.Iterator.Element == Element>(with possiblePrefix: PossiblePrefix) -> Bool
		
		/// Returns a Boolean value indicating whether this sequence and another
		/// sequence contain the same elements in the same order.
		///
		/// At least one of the sequences must be finite.
		///
		/// This example tests whether one countable range shares the same elements
		/// as another countable range and an array.
		///
		///     let a = 1...3
		///     let b = 1...10
		///
		///     print(a.elementsEqual(b))
		///     // Prints "false"
		///     print(a.elementsEqual([1, 2, 3]))
		///     // Prints "true"
		///
		/// - Parameter other: A sequence to compare to this sequence.
		/// - Returns: `true` if this sequence and `other` contain the same elements
		///   in the same order.
		///
		/// - SeeAlso: `elementsEqual(_:by:)`
		public func elementsEqual<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence) -> Bool
	}
	
	extension ContiguousArray where Element == String {
		
		/// Returns a new string by concatenating the elements of the sequence,
		/// adding the given separator between each element.
		///
		/// The following example shows how an array of strings can be joined to a
		/// single, comma-separated string:
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let list = cast.joined(separator: ", ")
		///     print(list)
		///     // Prints "Vivien, Marlon, Kim, Karl"
		///
		/// - Parameter separator: A string to insert between each of the elements
		///   in this sequence. The default separator is an empty string.
		/// - Returns: A single, concatenated string.
		public func joined(separator: String = default) -> String
	}
	
	extension ContiguousArray where Element : Collection {
		
		/// Returns the elements of this collection of collections, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   collection of collections.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenCollection<ContiguousArray<Element>>
	}
	
	extension ContiguousArray where Element : BidirectionalCollection {
		
		/// Returns the elements of this collection of collections, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   collection of collections.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenBidirectionalCollection<ContiguousArray<Element>>
	}
	
	extension ContiguousArray where Element : Sequence {
		
		/// Returns the elements of this sequence of sequences, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   sequence of sequences.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenSequence<ContiguousArray<Element>>
		
		/// Returns the concatenated elements of this sequence of sequences,
		/// inserting the given separator between each element.
		///
		/// This example shows how an array of `[Int]` instances can be joined, using
		/// another `[Int]` instance as the separator:
		///
		///     let nestedNumbers = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
		///     let joined = nestedNumbers.joined(separator: [-1, -2])
		///     print(Array(joined))
		///     // Prints "[1, 2, 3, -1, -2, 4, 5, 6, -1, -2, 7, 8, 9]"
		///
		/// - Parameter separator: A sequence to insert between each of this
		///   sequence's elements.
		/// - Returns: The joined sequence of elements.
		///
		/// - SeeAlso: `joined()`
		public func joined<Separator : Sequence where Separator.Iterator.Element == Iterator.Element.Iterator.Element>(separator: Separator) -> JoinedSequence<ContiguousArray<Element>>
	}
	
	extension ContiguousArray where Element : Comparable {
		
		/// Returns the elements of the sequence, sorted.
		///
		/// You can sort any sequence of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let sortedStudents = students.sorted()
		///     print(sortedStudents)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your sequence in descending order, pass the
		/// greater-than operator (`>`) to the `sorted(by:)` method.
		///
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Returns: A sorted array of the sequence's elements.
		///
		/// - SeeAlso: `sorted(by:)`
		///
		public func sorted() -> [Element]
		
		/// Returns the elements of the collection, sorted.
		///
		/// You can sort any collection of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let sortedStudents = students.sorted()
		///     print(sortedStudents)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your collection in descending order, pass the
		/// greater-than operator (`>`) to the `sorted(by:)` method.
		///
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Returns: A sorted array of the collection's elements.
		///
		/// - SeeAlso: `sorted(by:)`
		/// - MutatingVariant: sort
		public func sorted() -> [Element]
		
		/// Sorts the collection in place.
		///
		/// You can sort any mutable collection of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     var students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     students.sort()
		///     print(students)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your collection in descending order, pass the
		/// greater-than operator (`>`) to the `sort(by:)` method.
		///
		///     students.sort(by: >)
		///     print(students)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		public mutating func sort()
		
		/// Returns the minimum element in the sequence.
		///
		/// This example finds the smallest value in an array of height measurements.
		///
		///     let heights = [67.5, 65.7, 64.3, 61.1, 58.5, 60.3, 64.9]
		///     let lowestHeight = heights.min()
		///     print(lowestHeight)
		///     // Prints "Optional(58.5)"
		///
		/// - Returns: The sequence's minimum element. If the sequence has no
		///   elements, returns `nil`.
		///
		/// - SeeAlso: `min(by:)`
		@warn_unqualified_access
		public func min() -> Element?
		
		/// Returns the maximum element in the sequence.
		///
		/// This example finds the smallest value in an array of height measurements.
		///
		///     let heights = [67.5, 65.7, 64.3, 61.1, 58.5, 60.3, 64.9]
		///     let greatestHeight = heights.max()
		///     print(greatestHeight)
		///     // Prints "Optional(67.5)"
		///
		/// - Returns: The sequence's maximum element. If the sequence has no
		///   elements, returns `nil`.
		///
		/// - SeeAlso: `max(by:)`
		@warn_unqualified_access
		public func max() -> Element?
		
		/// Returns a Boolean value indicating whether the sequence precedes another
		/// sequence in a lexicographical (dictionary) ordering, using the
		/// less-than operator (`<`) to compare elements.
		///
		/// This example uses the `lexicographicallyPrecedes` method to test which
		/// array of integers comes first in a lexicographical ordering.
		///
		///     let a = [1, 2, 2, 2]
		///     let b = [1, 2, 3, 4]
		///
		///     print(a.lexicographicallyPrecedes(b))
		///     // Prints "true"
		///     print(b.lexicographicallyPrecedes(b))
		///     // Prints "false"
		///
		/// - Parameter other: A sequence to compare to this sequence.
		/// - Returns: `true` if this sequence precedes `other` in a dictionary
		///   ordering; otherwise, `false`.
		///
		/// - Note: This method implements the mathematical notion of lexicographical
		///   ordering, which has no connection to Unicode.  If you are sorting
		///   strings to present to the end user, use `String` APIs that
		///   perform localized comparison.
		/// - SeeAlso: `lexicographicallyPrecedes(_:by:)`
		public func lexicographicallyPrecedes<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence) -> Bool
	}
	
	/// A slice of an `Array`, `ContiguousArray`, or `ArraySlice` instance.
	///
	/// The `ArraySlice` type makes it fast and efficient for you to perform
	/// operations on sections of a larger array. Instead of copying over the
	/// elements of a slice to new storage, an `ArraySlice` instance presents a
	/// view onto the storage of a larger array. And because `ArraySlice`
	/// presents the same interface as `Array`, you can generally perform the
	/// same operations on a slice as you could on the original array.
	///
	/// For more information about using arrays, see `Array` and `ContiguousArray`,
	/// with which `ArraySlice` shares most properties and methods.
	///
	/// Slices Are Views onto Arrays
	/// ============================
	///
	/// For example, suppose you have an array holding the number of absences
	/// from each class during a session.
	///
	///     let absences = [0, 2, 0, 4, 0, 3, 1, 0]
	///
	/// You want to compare the absences in the first half of the session with
	/// those in the second half. To do so, start by creating two slices of the
	/// `absences` array.
	///
	///     let midpoint = absences.count / 2
	///
	///     let firstHalf = absences.prefix(upTo: midpoint)
	///     let secondHalf = absences.suffix(from: midpoint)
	///
	/// Neither the `firstHalf` nor `secondHalf` slices allocate any new storage
	/// of their own. Instead, each presents a view onto the storage of the
	/// `absences` array.
	///
	/// You can call any method on the slices that you might have called on the
	/// `absences` array. To learn which half had more absences, use the
	/// `reduce(_:_:)` method to calculate each sum.
	///
	///     let firstHalfSum = firstHalf.reduce(0, +)
	///     let secondHalfSum = secondHalf.reduce(0, +)
	///
	///     if firstHalfSum > secondHalfSum {
	///         print("More absences in the first half.")
	///     } else {
	///         print("More absences in the second half.")
	///     }
	///     // Prints "More absences in the second half."
	///
	/// - Important: Long-term storage of `ArraySlice` instances is discouraged. A
	///   slice holds a reference to the entire storage of a larger array, not
	///   just to the portion it presents, even after the original array's lifetime
	///   ends. Long-term storage of a slice may therefore prolong the lifetime of
	///   elements that are no longer otherwise accessible, which can appear to be
	///   memory and object leakage.
	///
	/// Slices Maintain Indices
	/// =======================
	///
	/// Unlike `Array` and `ContiguousArray`, the starting index for an
	/// `ArraySlice` instance isn't always zero. Slices maintain the same
	/// indices of the larger array for the same elements, so the starting
	/// index of a slice depends on how it was created, letting you perform
	/// index-based operations on either a full array or a slice.
	///
	/// Sharing indices between collections and their subsequences is an important
	/// part of the design of Swift's collection algorithms. Suppose you are
	/// tasked with finding the first two days with absences in the session. To
	/// find the indices of the two days in question, follow these steps:
	///
	/// 1) Call `index(where:)` to find the index of the first element in the
	///    `absences` array that is greater than zero.
	/// 2) Create a slice of the `absences` array starting after the index found in
	///    step 1.
	/// 3) Call `index(where:)` again, this time on the slice created in step 2.
	///    Where in some languages you might pass a starting index into an
	///    `indexOf` method to find the second day, in Swift you perform the same
	///    operation on a slice of the original array.
	/// 4) Print the results using the indices found in steps 1 and 3 on the
	///    original `absences` array.
	///
	/// Here's an implementation of those steps:
	///
	///     if let i = absences.index(where: { $0 > 0 }) {                      // 1
	///         let absencesAfterFirst = absences.suffix(from: i + 1)           // 2
	///         if let j = absencesAfterFirst.index(where: { $0 > 0 }) {        // 3
	///             print("The first day with absences had \(absences[i]).")    // 4
	///             print("The second day with absences had \(absences[j]).")
	///         }
	///     }
	///     // Prints "The first day with absences had 2."
	///     // Prints "The second day with absences had 4."
	///
	/// In particular, note that `j`, the index of the second day with absences,
	/// was found in a slice of the original array and then used to access a value
	/// in the original `absences` array itself.
	///
	/// - Note: To safely reference the starting and ending indices of a slice,
	///   always use the `startIndex` and `endIndex` properties instead of
	///   specific values.
	public struct ArraySlice<Element> : RandomAccessCollection, MutableCollection {
		
		/// A type that represents a position in the collection.
		///
		/// Valid indices consist of the position of every element and a
		/// "past the end" position that's not valid for use as a subscript
		/// argument.
		///
		/// - SeeAlso: endIndex
		public typealias Index = Int
		
		/// A type that provides the sequence's iteration interface and
		/// encapsulates its iteration state.
		public typealias Iterator = IndexingIterator<ArraySlice<Element>>
		
		/// The position of the first element in a nonempty array.
		///
		/// If the array is empty, `startIndex` is equal to `endIndex`.
		public var startIndex: Int { get }
		
		/// The array's "past the end" position---that is, the position one greater
		/// than the last valid subscript argument.
		///
		/// When you need a range that includes the last element of an array, use the
		/// half-open range operator (`..<`) with `endIndex`. The `..<` operator
		/// creates a range that doesn't include the upper bound, so it's always
		/// safe to use with `endIndex`. For example:
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     if let i = numbers.index(of: 30) {
		///         print(numbers[i ..< numbers.endIndex])
		///     }
		///     // Prints "[30, 40, 50]"
		///
		/// If the array is empty, `endIndex` is equal to `startIndex`.
		public var endIndex: Int { get }
		
		/// Returns the position immediately after the given index.
		///
		/// - Parameter i: A valid index of the collection. `i` must be less than
		///   `endIndex`.
		/// - Returns: The index value immediately after `i`.
		public func index(after i: Int) -> Int
		
		/// Replaces the given index with its successor.
		///
		/// - Parameter i: A valid index of the collection. `i` must be less than
		///   `endIndex`.
		public func formIndex(after i: inout Int)
		
		/// Returns the position immediately before the given index.
		///
		/// - Parameter i: A valid index of the collection. `i` must be greater than
		///   `startIndex`.
		/// - Returns: The index value immediately before `i`.
		public func index(before i: Int) -> Int
		
		/// Replaces the given index with its predecessor.
		///
		/// - Parameter i: A valid index of the collection. `i` must be greater than
		///   `startIndex`.
		public func formIndex(before i: inout Int)
		
		/// Returns an index that is the specified distance from the given index.
		///
		/// The following example obtains an index advanced four positions from an
		/// array's starting index and then prints the element at that position.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     let i = numbers.index(numbers.startIndex, offsetBy: 4)
		///     print(numbers[i])
		///     // Prints "50"
		///
		/// Advancing an index beyond a collection's ending index or offsetting it
		/// before a collection's starting index may trigger a runtime error. The
		/// value passed as `n` must not result in such an operation.
		///
		/// - Parameters:
		///   - i: A valid index of the array.
		///   - n: The distance to offset `i`.
		/// - Returns: An index offset by `n` from the index `i`. If `n` is positive,
		///   this is the same value as the result of `n` calls to `index(after:)`.
		///   If `n` is negative, this is the same value as the result of `-n` calls
		///   to `index(before:)`.
		///
		/// - Complexity: O(1)
		public func index(_ i: Int, offsetBy n: Int) -> Int
		
		/// Returns an index that is the specified distance from the given index,
		/// unless that distance is beyond a given limiting index.
		///
		/// The following example obtains an index advanced four positions from an
		/// array's starting index and then prints the element at that position. The
		/// operation doesn't require going beyond the limiting `numbers.endIndex`
		/// value, so it succeeds.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     let i = numbers.index(numbers.startIndex,
		///                           offsetBy: 4,
		///                           limitedBy: numbers.endIndex)
		///     print(numbers[i])
		///     // Prints "50"
		///
		/// The next example attempts to retrieve an index ten positions from
		/// `numbers.startIndex`, but fails, because that distance is beyond the
		/// index passed as `limit`.
		///
		///     let j = numbers.index(numbers.startIndex,
		///                           offsetBy: 10,
		///                           limitedBy: numbers.endIndex)
		///     print(j)
		///     // Prints "nil"
		///
		/// Advancing an index beyond a collection's ending index or offsetting it
		/// before a collection's starting index may trigger a runtime error. The
		/// value passed as `n` must not result in such an operation.
		///
		/// - Parameters:
		///   - i: A valid index of the array.
		///   - n: The distance to offset `i`.
		///   - limit: A valid index of the collection to use as a limit. If `n > 0`,
		///     `limit` has no effect if it is less than `i`. Likewise, if `n < 0`,
		///     `limit` has no effect if it is greater than `i`.
		/// - Returns: An index offset by `n` from the index `i`, unless that index
		///   would be beyond `limit` in the direction of movement. In that case,
		///   the method returns `nil`.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1)
		public func index(_ i: Int, offsetBy n: Int, limitedBy limit: Int) -> Int?
		
		/// Returns the distance between two indices.
		///
		/// - Parameters:
		///   - start: A valid index of the collection.
		///   - end: Another valid index of the collection. If `end` is equal to
		///     `start`, the result is zero.
		/// - Returns: The distance between `start` and `end`.
		public func distance(from start: Int, to end: Int) -> Int
		
		/// A type that can represent the indices that are valid for subscripting the
		/// collection, in ascending order.
		public typealias Indices = CountableRange<Int>
		
		/// Accesses the element at the specified position.
		///
		/// The following example uses indexed subscripting to update an array's
		/// second element. After assigning the new value (`"Butler"`) at a specific
		/// position, that value is immediately available at that same position.
		///
		///     var streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     streets[1] = "Butler"
		///     print(streets[1])
		///     // Prints "Butler"
		///
		/// - Parameter index: The position of the element to access. `index` must be
		///   greater than or equal to `startIndex` and less than `endIndex`.
		///
		/// - Complexity: Reading an element from an array is O(1). Writing is O(1)
		///   unless the array's storage is shared with another array, in which case
		///   writing is O(*n*), where *n* is the length of the array.
		public subscript(index: Int) -> Element
		
		/// Accesses a contiguous subrange of the array's elements.
		///
		/// The returned `ArraySlice` instance uses the same indices for the same
		/// elements as the original array. In particular, that slice, unlike an
		/// array, may have a nonzero `startIndex` and an `endIndex` that is not
		/// equal to `count`. Always use the slice's `startIndex` and `endIndex`
		/// properties instead of assuming that its indices start or end at a
		/// particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let i = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[i!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of integers. The bounds of the range must be
		///   valid indices of the array.
		public subscript(bounds: Range<Int>) -> ArraySlice<Element>
		
		/// Calls a closure with a pointer to the array's contiguous storage.
		///
		///
		/// Often, the optimizer can eliminate bounds checks within an array
		/// algorithm, but when that fails, invoking the same algorithm on the
		/// buffer pointer passed into your closure lets you trade safety for speed.
		///
		/// The following example shows how you can iterate over the contents of the
		/// buffer pointer:
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     let sum = numbers.withUnsafeBufferPointer { buffer -> Int in
		///         var result = 0
		///         for i in stride(from: buffer.startIndex, to: buffer.endIndex, by: 2) {
		///             result += buffer[i]
		///         }
		///         return result
		///     }
		///     // 'sum' == 9
		///
		/// - Parameter body: A closure with an `UnsafeBufferPointer` parameter that
		///   points to the contiguous storage for the array. If `body` has a return
		///   value, it is used as the return value for the
		///   `withUnsafeBufferPointer(_:)` method. The pointer argument is valid
		///   only for the duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeMutableBufferPointer`, `UnsafeBufferPointer`
		public func withUnsafeBufferPointer<R>(_ body: (UnsafeBufferPointer<Element>) throws -> R) rethrows -> R
		
		/// Calls the given closure with a pointer to the array's mutable contiguous
		/// storage.
		///
		/// Often, the optimizer can eliminate bounds checks within an array
		/// algorithm, but when that fails, invoking the same algorithm on the
		/// buffer pointer passed into your closure lets you trade safety for speed.
		///
		/// The following example shows modifying the contents of the
		/// `UnsafeMutableBufferPointer` argument to `body` alters the contents of
		/// the array:
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.withUnsafeMutableBufferPointer { buffer in
		///         for i in stride(from: buffer.startIndex, to: buffer.endIndex - 1, by: 2) {
		///             swap(&buffer[i], &buffer[i + 1])
		///         }
		///     }
		///     print(numbers)
		///     // Prints "[2, 1, 4, 3, 5]"
		///
		/// - Warning: Do not rely on anything about `self` (the array that is the
		///   target of this method) during the execution of the `body` closure: It
		///   may not appear to have its correct value.  Instead, use only the
		///   `UnsafeMutableBufferPointer` argument to `body`.
		///
		/// - Parameter body: A closure with an `UnsafeMutableBufferPointer`
		///   parameter that points to the contiguous storage for the array. If
		///   `body` has a return value, it is used as the return value for the
		///   `withUnsafeMutableBufferPointer(_:)` method. The pointer argument is
		///   valid only for the duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeBufferPointer`, `UnsafeMutableBufferPointer`
		public mutating func withUnsafeMutableBufferPointer<R>(_ body: (inout UnsafeMutableBufferPointer<Element>) throws -> R) rethrows -> R
		
		/// Replaces a range of elements with the elements in the specified
		/// collection.
		///
		/// This method has the effect of removing the specified range of elements
		/// from the array and inserting the new elements at the same location. The
		/// number of new elements need not match the number of elements being
		/// removed.
		///
		/// In this example, three elements in the middle of an array of integers are
		/// replaced by the five elements of a `Repeated<Int>` instance.
		///
		///      var nums = [10, 20, 30, 40, 50]
		///      nums.replaceSubrange(1...3, with: repeatElement(1, count: 5))
		///      print(nums)
		///      // Prints "[10, 1, 1, 1, 1, 1, 50]"
		///
		/// If you pass a zero-length range as the `subrange` parameter, this method
		/// inserts the elements of `newElements` at `subrange.startIndex`. Calling
		/// the `insert(contentsOf:at:)` method instead is preferred.
		///
		/// Likewise, if you pass a zero-length collection as the `newElements`
		/// parameter, this method removes the elements in the given subrange
		/// without replacement. Calling the `removeSubrange(_:)` method instead is
		/// preferred.
		///
		/// - Parameters:
		///   - subrange: The subrange of the array to replace. The start and end of
		///     a subrange must be valid indices of the array.
		///   - newElements: The new elements to add to the array.
		///
		/// - Complexity: O(`subrange.count`) if you are replacing a suffix of the
		///   array with an empty collection; otherwise, O(*n*), where *n* is the
		///   length of the array.
		public mutating func replaceSubrange<C where C : Collection, C.Iterator.Element == _Buffer.Element>(_ subrange: Range<Int>, with newElements: C)
		
		/// Calls a closure with a view of the array's underlying bytes of memory as a
		/// Collection of `UInt8`.
		///
		///  If no such storage exists, it is first created.
		///
		/// - Precondition: `Pointee` is a trivial type.
		///
		/// The following example shows how you copy bytes into an array:
		///
		///    var numbers = [Int32](repeating: 0, count: 2)
		///    var byteValues: [UInt8] = [0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00]
		///    numbers.withUnsafeMutableBytes { destBytes in
		///      byteValues.withUnsafeBytes { srcBytes in
		///        destBytes.copyBytes(from: srcBytes)
		///      }
		///    }
		///
		/// - Parameter body: A closure with an `UnsafeRawBufferPointer`
		///   parameter that points to the contiguous storage for the array. If `body`
		///   has a return value, it is used as the return value for the
		///   `withUnsafeMutableBytes(_:)` method. The argument is valid only for the
		///   duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeBytes`, `UnsafeMutableRawBufferPointer`
		public mutating func withUnsafeMutableBytes<R>(_ body: (UnsafeMutableRawBufferPointer) throws -> R) rethrows -> R
		
		/// Calls a closure with a view of the array's underlying bytes of memory
		/// as a Collection of `UInt8`.
		///
		///  If no such storage exists, it is first created.
		///
		/// - Precondition: `Pointee` is a trivial type.
		///
		/// The following example shows how you copy the contents of an array into a
		/// buffer of `UInt8`:
		///
		///    let numbers = [1, 2, 3]
		///    var byteBuffer = [UInt8]()
		///    numbers.withUnsafeBytes {
		///        byteBuffer += $0
		///    }
		///
		/// - Parameter body: A closure with an `UnsafeRawBufferPointer` parameter
		///   that points to the contiguous storage for the array. If `body` has a
		///   return value, it is used as the return value for the
		///   `withUnsafeBytes(_:)` method. The argument is valid only for the
		///   duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeBytes`, `UnsafeRawBufferPointer`
		public func withUnsafeBytes<R>(_ body: (UnsafeRawBufferPointer) throws -> R) rethrows -> R
		
		/// Removes and returns the last element of the collection.
		///
		/// - Returns: The last element of the collection if the collection has one
		///   or more elements; otherwise, `nil`.
		///
		/// - Complexity: O(1).
		/// - SeeAlso: `removeLast()`
		public mutating func popLast() -> Element?
		
		/// Removes and returns the last element of the collection.
		///
		/// The collection must not be empty.
		///
		/// - Returns: The last element of the collection.
		///
		/// - Complexity: O(1)
		/// - SeeAlso: `popLast()`
		public mutating func removeLast() -> Element
		
		/// Removes the given number of elements from the end of the collection.
		///
		/// - Parameter n: The number of elements to remove. `n` must be greater
		///   than or equal to zero, and must be less than or equal to the number of
		///   elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the length
		///   of the collection.
		public mutating func removeLast(_ n: Int)
		
		/// Returns a subsequence containing all but the specified number of final
		/// elements.
		///
		/// If the number of elements to drop exceeds the number of elements in the
		/// collection, the result is an empty subsequence.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropLast(2))
		///     // Prints "[1, 2, 3]"
		///     print(numbers.dropLast(10))
		///     // Prints "[]"
		///
		/// - Parameter n: The number of elements to drop off the end of the
		///   collection. `n` must be greater than or equal to zero.
		/// - Returns: A subsequence that leaves off `n` elements from the end.
		///
		/// - Complexity: O(*n*), where *n* is the number of elements to drop.
		public func dropLast(_ n: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence, up to the given maximum length, containing the
		/// final elements of the collection.
		///
		/// If the maximum length exceeds the number of elements in the collection,
		/// the result contains the entire collection.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.suffix(2))
		///     // Prints "[4, 5]"
		///     print(numbers.suffix(10))
		///     // Prints "[1, 2, 3, 4, 5]"
		///
		/// - Parameter maxLength: The maximum number of elements to return.
		///   `maxLength` must be greater than or equal to zero.
		/// - Returns: A subsequence terminating at the end of the collection with at
		///   most `maxLength` elements.
		///
		/// - Complexity: O(*n*), where *n* is equal to `maxLength`.
		public func suffix(_ maxLength: Int) -> ArraySlice<Element>
		
		/// Removes and returns the first element of the collection.
		///
		/// - Returns: The first element of the collection if the collection is
		///   not empty; otherwise, `nil`.
		///
		/// - Complexity: O(1)
		public mutating func popFirst() -> Element?
		
		/// Returns an array containing the results of mapping the given closure
		/// over the sequence's elements.
		///
		/// In this example, `map` is used first to convert the names in the array
		/// to lowercase strings and then to count their characters.
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let lowercaseNames = cast.map { $0.lowercaseString }
		///     // 'lowercaseNames' == ["vivien", "marlon", "kim", "karl"]
		///     let letterCounts = cast.map { $0.characters.count }
		///     // 'letterCounts' == [6, 6, 3, 4]
		///
		/// - Parameter transform: A mapping closure. `transform` accepts an
		///   element of this sequence as its parameter and returns a transformed
		///   value of the same or of a different type.
		/// - Returns: An array containing the transformed elements of this
		///   sequence.
		public func map<T>(_ transform: (Element) throws -> T) rethrows -> [T]
		
		/// Returns a subsequence containing all but the given number of initial
		/// elements.
		///
		/// If the number of elements to drop exceeds the number of elements in
		/// the collection, the result is an empty subsequence.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropFirst(2))
		///     // Prints "[3, 4, 5]"
		///     print(numbers.dropFirst(10))
		///     // Prints "[]"
		///
		/// - Parameter n: The number of elements to drop from the beginning of
		///   the collection. `n` must be greater than or equal to zero.
		/// - Returns: A subsequence starting after the specified number of
		///   elements.
		///
		/// - Complexity: O(*n*), where *n* is the number of elements to drop from
		///   the beginning of the collection.
		public func dropFirst(_ n: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence, up to the specified maximum length, containing
		/// the initial elements of the collection.
		///
		/// If the maximum length exceeds the number of elements in the collection,
		/// the result contains all the elements in the collection.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.prefix(2))
		///     // Prints "[1, 2]"
		///     print(numbers.prefix(10))
		///     // Prints "[1, 2, 3, 4, 5]"
		///
		/// - Parameter maxLength: The maximum number of elements to return.
		///   `maxLength` must be greater than or equal to zero.
		/// - Returns: A subsequence starting at the beginning of this collection
		///   with at most `maxLength` elements.
		public func prefix(_ maxLength: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence from the start of the collection up to, but not
		/// including, the specified position.
		///
		/// The resulting subsequence *does not include* the element at the position
		/// `end`. The following example searches for the index of the number `40`
		/// in an array of integers, and then prints the prefix of the array up to,
		/// but not including, that index:
		///
		///     let numbers = [10, 20, 30, 40, 50, 60]
		///     if let i = numbers.index(of: 40) {
		///         print(numbers.prefix(upTo: i))
		///     }
		///     // Prints "[10, 20, 30]"
		///
		/// Passing the collection's starting index as the `end` parameter results in
		/// an empty subsequence.
		///
		///     print(numbers.prefix(upTo: numbers.startIndex))
		///     // Prints "[]"
		///
		/// - Parameter end: The "past the end" index of the resulting subsequence.
		///   `end` must be a valid index of the collection.
		/// - Returns: A subsequence up to, but not including, the `end` position.
		///
		/// - Complexity: O(1)
		/// - SeeAlso: `prefix(through:)`
		public func prefix(upTo end: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence from the specified position to the end of the
		/// collection.
		///
		/// The following example searches for the index of the number `40` in an
		/// array of integers, and then prints the suffix of the array starting at
		/// that index:
		///
		///     let numbers = [10, 20, 30, 40, 50, 60]
		///     if let i = numbers.index(of: 40) {
		///         print(numbers.suffix(from: i))
		///     }
		///     // Prints "[40, 50, 60]"
		///
		/// Passing the collection's `endIndex` as the `start` parameter results in
		/// an empty subsequence.
		///
		///     print(numbers.suffix(from: numbers.endIndex))
		///     // Prints "[]"
		///
		/// - Parameter start: The index at which to start the resulting subsequence.
		///   `start` must be a valid index of the collection.
		/// - Returns: A subsequence starting at the `start` position.
		///
		/// - Complexity: O(1)
		public func suffix(from start: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence from the start of the collection through the
		/// specified position.
		///
		/// The resulting subsequence *includes* the element at the position `end`.
		/// The following example searches for the index of the number `40` in an
		/// array of integers, and then prints the prefix of the array up to, and
		/// including, that index:
		///
		///     let numbers = [10, 20, 30, 40, 50, 60]
		///     if let i = numbers.index(of: 40) {
		///         print(numbers.prefix(through: i))
		///     }
		///     // Prints "[10, 20, 30, 40]"
		///
		/// - Parameter end: The index of the last element to include in the
		///   resulting subsequence. `end` must be a valid index of the collection
		///   that is not equal to the `endIndex` property.
		/// - Returns: A subsequence up to, and including, the `end` position.
		///
		/// - Complexity: O(1)
		/// - SeeAlso: `prefix(upTo:)`
		public func prefix(through position: Int) -> ArraySlice<Element>
		
		/// Returns the longest possible subsequences of the collection, in order,
		/// that don't contain elements satisfying the given predicate.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the sequence are not returned as part of
		/// any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string using a
		/// closure that matches spaces. The first use of `split` returns each word
		/// that was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(whereSeparator: { $0 == " " })
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(
		///         line.characters.split(
		///             maxSplits: 1, whereSeparator: { $0 == " " }
		///             ).map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(omittingEmptySubsequences: false, whereSeparator: { $0 == " " })
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - maxSplits: The maximum number of times to split the collection, or
		///     one less than the number of subsequences to return. If
		///     `maxSplits + 1` subsequences are returned, the last one is a suffix
		///     of the original collection containing the remaining elements.
		///     `maxSplits` must be greater than or equal to zero. The default value
		///     is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each pair of consecutive elements
		///     satisfying the `isSeparator` predicate and for each element at the
		///     start or end of the collection satisfying the `isSeparator`
		///     predicate. The default value is `true`.
		///   - isSeparator: A closure that takes an element as an argument and
		///     returns a Boolean value indicating whether the collection should be
		///     split at that element.
		/// - Returns: An array of subsequences, split from this collection's
		///   elements.
		public func split(maxSplits: Int = default, omittingEmptySubsequences: Bool = default, whereSeparator isSeparator: (Element) throws -> Bool) rethrows -> [ArraySlice<Element>]
		
		/// Removes and returns the first element of the collection.
		///
		/// The collection must not be empty.
		///
		/// - Returns: The first element of the collection.
		///
		/// - Complexity: O(1)
		/// - SeeAlso: `popFirst()`
		public mutating func removeFirst() -> Element
		
		/// Removes the specified number of elements from the beginning of the
		/// collection.
		///
		/// - Parameter n: The number of elements to remove. `n` must be greater than
		///   or equal to zero, and must be less than or equal to the number of
		///   elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*).
		public mutating func removeFirst(_ n: Int)
		
		/// The last element of the collection.
		///
		/// If the collection is empty, the value of this property is `nil`.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     if let lastNumber = numbers.last {
		///         print(lastNumber)
		///     }
		///     // Prints "50"
		public var last: Element? { get }
		
		/// Returns the first index in which an element of the collection satisfies
		/// the given predicate.
		///
		/// You can use the predicate to find an element of a type that doesn't
		/// conform to the `Equatable` protocol or to find an element that matches
		/// particular criteria. Here's an example that finds a student name that
		/// begins with the letter "A":
		///
		///     let students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     if let i = students.index(where: { $0.hasPrefix("A") }) {
		///         print("\(students[i]) starts with 'A'!")
		///     }
		///     // Prints "Abena starts with 'A'!"
		///
		/// - Parameter predicate: A closure that takes an element as its argument
		///   and returns a Boolean value that indicates whether the passed element
		///   represents a match.
		/// - Returns: The index of the first element for which `predicate` returns
		///   `true`. If no elements in the collection satisfy the given predicate,
		///   returns `nil`.
		///
		/// - SeeAlso: `index(of:)`
		public func index(where predicate: (Element) throws -> Bool) rethrows -> Int?
		
		public mutating func partition(by belongsInSecondPartition: (Element) throws -> Bool) rethrows -> Int
		
		public mutating func partition(by belongsInSecondPartition: (Element) throws -> Bool) rethrows -> Int
		
		/// Returns the elements of the collection, sorted using the given
		/// predicate as the comparison between elements.
		///
		/// When you want to sort a collection of elements that don't conform to
		/// the `Comparable` protocol, pass a predicate to this method that returns
		/// `true` when the first element passed should be ordered before the
		/// second. The elements of the resulting array are ordered according to the
		/// given predicate.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also `true`.
		///   (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements for which `areInIncreasingOrder` does not
		/// establish an order.
		///
		/// In the following example, the predicate provides an ordering for an array
		/// of a custom `HTTPResponse` type. The predicate orders errors before
		/// successes and sorts the error responses by their error code.
		///
		///     enum HTTPResponse {
		///         case ok
		///         case error(Int)
		///     }
		///
		///     let responses: [HTTPResponse] = [.error(500), .ok, .ok, .error(404), .error(403)]
		///     let sortedResponses = responses.sorted {
		///         switch ($0, $1) {
		///         // Order errors by code
		///         case let (.error(aCode), .error(bCode)):
		///             return aCode < bCode
		///
		///         // All successes are equivalent, so none is before any other
		///         case (.ok, .ok): return false
		///
		///         // Order errors before successes
		///         case (.error, .ok): return true
		///         case (.ok, .error): return false
		///         }
		///     }
		///     print(sortedResponses)
		///     // Prints "[.error(403), .error(404), .error(500), .ok, .ok]"
		///
		/// You also use this method to sort elements that conform to the
		/// `Comparable` protocol in descending order. To sort your collection
		/// in descending order, pass the greater-than operator (`>`) as the
		/// `areInIncreasingOrder` parameter.
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// Calling the related `sorted()` method is equivalent to calling this
		/// method and passing the less-than operator (`<`) as the predicate.
		///
		///     print(students.sorted())
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///     print(students.sorted(by: <))
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// - Parameter areInIncreasingOrder: A predicate that returns `true` if its first
		///   argument should be ordered before its second argument; otherwise,
		///   `false`.
		/// - Returns: A sorted array of the collection's elements.
		///
		/// - SeeAlso: `sorted()`
		/// - MutatingVariant: sort
		public func sorted(by areInIncreasingOrder: (Element, Element) -> Bool) -> [Element]
		
		/// Sorts the collection in place, using the given predicate as the
		/// comparison between elements.
		///
		/// When you want to sort a collection of elements that doesn't conform to
		/// the `Comparable` protocol, pass a closure to this method that returns
		/// `true` when the first element passed should be ordered before the
		/// second.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also `true`.
		///   (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements for which `areInIncreasingOrder` does not
		/// establish an order.
		///
		/// In the following example, the closure provides an ordering for an array
		/// of a custom enumeration that describes an HTTP response. The predicate
		/// orders errors before successes and sorts the error responses by their
		/// error code.
		///
		///     enum HTTPResponse {
		///         case ok
		///         case error(Int)
		///     }
		///
		///     var responses: [HTTPResponse] = [.error(500), .ok, .ok, .error(404), .error(403)]
		///     responses.sort {
		///         switch ($0, $1) {
		///         // Order errors by code
		///         case let (.error(aCode), .error(bCode)):
		///             return aCode < bCode
		///
		///         // All successes are equivalent, so none is before any other
		///         case (.ok, .ok): return false
		///
		///         // Order errors before successes
		///         case (.error, .ok): return true
		///         case (.ok, .error): return false
		///         }
		///     }
		///     print(responses)
		///     // Prints "[.error(403), .error(404), .error(500), .ok, .ok]"
		///
		/// Alternatively, use this method to sort a collection of elements that do
		/// conform to `Comparable` when you want the sort to be descending instead
		/// of ascending. Pass the greater-than operator (`>`) operator as the
		/// predicate.
		///
		///     var students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     students.sort(by: >)
		///     print(students)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Parameter areInIncreasingOrder: A predicate that returns `true` if its first
		///   argument should be ordered before its second argument; otherwise,
		///   `false`.
		public mutating func sort(by areInIncreasingOrder: (Element, Element) -> Bool)
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[index!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: ClosedRange<Int>) -> ArraySlice<Element> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[index!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableRange<Int>) -> ArraySlice<Element> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[index!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableClosedRange<Int>) -> ArraySlice<Element> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: ClosedRange<Int>) -> ArraySlice<Element>
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableRange<Int>) -> ArraySlice<Element>
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableClosedRange<Int>) -> ArraySlice<Element>
		
		/// A sequence containing the same elements as this sequence,
		/// but on which some operations, such as `map` and `filter`, are
		/// implemented lazily.
		///
		/// - SeeAlso: `LazySequenceProtocol`, `LazySequence`
		public var lazy: LazySequence<ArraySlice<Element>> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: Range<Int>) -> MutableSlice<ArraySlice<Element>>
		
		/// The indices that are valid for subscripting the collection, in ascending
		/// order.
		///
		/// A collection's `indices` property can hold a strong reference to the
		/// collection itself, causing the collection to be non-uniquely referenced.
		/// If you mutate the collection while iterating over its indices, a strong
		/// reference can cause an unexpected copy of the collection. To avoid the
		/// unexpected copy, use the `index(after:)` method starting with
		/// `startIndex` to produce indices instead.
		///
		///     var c = MyFancyCollection([10, 20, 30, 40, 50])
		///     var i = c.startIndex
		///     while i != c.endIndex {
		///         c[i] /= 5
		///         i = c.index(after: i)
		///     }
		///     // c == MyFancyCollection([2, 4, 6, 8, 10])
		public var indices: CountableRange<Int> { get }
		
		/// Returns a view presenting the elements of the collection in reverse
		/// order.
		///
		/// You can reverse a collection without allocating new space for its
		/// elements by calling this `reversed()` method. A
		/// `ReversedRandomAccessCollection` instance wraps an underlying collection
		/// and provides access to its elements in reverse order. This example
		/// prints the elements of an array in reverse order:
		///
		///     let numbers = [3, 5, 7]
		///     for number in numbers.reversed() {
		///         print(number)
		///     }
		///     // Prints "7"
		///     // Prints "5"
		///     // Prints "3"
		///
		/// If you need a reversed collection of the same type, you may be able to
		/// use the collection's sequence-based or collection-based initializer. For
		/// example, to get the reversed version of an array, initialize a new
		/// `Array` instance from the result of this `reversed()` method.
		///
		///     let reversedNumbers = Array(numbers.reversed())
		///     print(reversedNumbers)
		///     // Prints "[7, 5, 3]"
		///
		/// - Complexity: O(1)
		public func reversed() -> ReversedRandomAccessCollection<ArraySlice<Element>>
		
		/// Returns an array containing the results of mapping the given closure
		/// over the sequence's elements.
		///
		/// In this example, `map` is used first to convert the names in the array
		/// to lowercase strings and then to count their characters.
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let lowercaseNames = cast.map { $0.lowercaseString }
		///     // 'lowercaseNames' == ["vivien", "marlon", "kim", "karl"]
		///     let letterCounts = cast.map { $0.characters.count }
		///     // 'letterCounts' == [6, 6, 3, 4]
		///
		/// - Parameter transform: A mapping closure. `transform` accepts an
		///   element of this sequence as its parameter and returns a transformed
		///   value of the same or of a different type.
		/// - Returns: An array containing the transformed elements of this
		///   sequence.
		public func map<T>(_ transform: (Element) throws -> T) rethrows -> [T]
		
		/// Returns an array containing, in order, the elements of the sequence
		/// that satisfy the given predicate.
		///
		/// In this example, `filter` is used to include only names shorter than
		/// five characters.
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let shortNames = cast.filter { $0.characters.count < 5 }
		///     print(shortNames)
		///     // Prints "["Kim", "Karl"]"
		///
		/// - Parameter shouldInclude: A closure that takes an element of the
		///   sequence as its argument and returns a Boolean value indicating
		///   whether the element should be included in the returned array.
		/// - Returns: An array of the elements that `includeElement` allowed.
		public func filter(_ isIncluded: (Element) throws -> Bool) rethrows -> [Element]
		
		/// Returns a value less than or equal to the number of elements in
		/// the sequence, nondestructively.
		///
		/// - Complexity: O(*n*)
		public var underestimatedCount: Int { get }
		
		/// Calls the given closure on each element in the sequence in the same order
		/// as a `for`-`in` loop.
		///
		/// The two loops in the following example produce the same output:
		///
		///     let numberWords = ["one", "two", "three"]
		///     for word in numberWords {
		///         print(word)
		///     }
		///     // Prints "one"
		///     // Prints "two"
		///     // Prints "three"
		///
		///     numberWords.forEach { word in
		///         print(word)
		///     }
		///     // Same as above
		///
		/// Using the `forEach` method is distinct from a `for`-`in` loop in two
		/// important ways:
		///
		/// 1. You cannot use a `break` or `continue` statement to exit the current
		///    call of the `body` closure or skip subsequent calls.
		/// 2. Using the `return` statement in the `body` closure will exit only from
		///    the current call to `body`, not from any outer scope, and won't skip
		///    subsequent calls.
		///
		/// - Parameter body: A closure that takes an element of the sequence as a
		///   parameter.
		public func forEach(_ body: (Element) throws -> Void) rethrows
		
		/// Returns the first element of the sequence that satisfies the given
		/// predicate or nil if no such element is found.
		///
		/// - Parameter predicate: A closure that takes an element of the
		///   sequence as its argument and returns a Boolean value indicating
		///   whether the element is a match.
		/// - Returns: The first match or `nil` if there was no match.
		public func first(where predicate: (Element) throws -> Bool) rethrows -> Element?
		
		/// Returns a subsequence containing all but the first element of the
		/// sequence.
		///
		/// The following example drops the first element from an array of integers.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropFirst())
		///     // Prints "[2, 3, 4, 5]"
		///
		/// If the sequence has no elements, the result is an empty subsequence.
		///
		///     let empty: [Int] = []
		///     print(empty.dropFirst())
		///     // Prints "[]"
		///
		/// - Returns: A subsequence starting after the first element of the
		///   sequence.
		///
		/// - Complexity: O(1)
		public func dropFirst() -> ArraySlice<Element>
		
		/// Returns a subsequence containing all but the last element of the
		/// sequence.
		///
		/// The sequence must be finite. If the sequence has no elements, the result
		/// is an empty subsequence.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropLast())
		///     // Prints "[1, 2, 3, 4]"
		///
		/// If the sequence has no elements, the result is an empty subsequence.
		///
		///     let empty: [Int] = []
		///     print(empty.dropLast())
		///     // Prints "[]"
		///
		/// - Returns: A subsequence leaving off the last element of the sequence.
		///
		/// - Complexity: O(*n*), where *n* is the length of the sequence.
		public func dropLast() -> ArraySlice<Element>
		
		/// Returns a sequence of pairs (*n*, *x*), where *n* represents a
		/// consecutive integer starting at zero, and *x* represents an element of
		/// the sequence.
		///
		/// This example enumerates the characters of the string "Swift" and prints
		/// each character along with its place in the string.
		///
		///     for (n, c) in "Swift".characters.enumerated() {
		///         print("\(n): '\(c)'")
		///     }
		///     // Prints "0: 'S'"
		///     // Prints "1: 'w'"
		///     // Prints "2: 'i'"
		///     // Prints "3: 'f'"
		///     // Prints "4: 't'"
		///
		/// When enumerating a collection, the integer part of each pair is a counter
		/// for the enumeration, not necessarily the index of the paired value.
		/// These counters can only be used as indices in instances of zero-based,
		/// integer-indexed collections, such as `Array` and `ContiguousArray`. For
		/// other collections the counters may be out of range or of the wrong type
		/// to use as an index. To iterate over the elements of a collection with its
		/// indices, use the `zip(_:_:)` function.
		///
		/// This example iterates over the indices and elements of a set, building a
		/// list of indices of names with five or fewer letters.
		///
		///     let names: Set = ["Sofia", "Camilla", "Martina", "Mateo", "Nicolás"]
		///     var shorterIndices: [SetIndex<String>] = []
		///     for (i, name) in zip(names.indices, names) {
		///         if name.characters.count <= 5 {
		///             shorterIndices.append(i)
		///         }
		///     }
		///
		/// Now that the `shorterIndices` array holds the indices of the shorter
		/// names in the `names` set, you can use those indices to access elements in
		/// the set.
		///
		///     for i in shorterIndices {
		///         print(names[i])
		///     }
		///     // Prints "Sofia"
		///     // Prints "Mateo"
		///
		/// - Returns: A sequence of pairs enumerating the sequence.
		public func enumerated() -> EnumeratedSequence<ArraySlice<Element>>
		
		/// Returns the minimum element in the sequence, using the given predicate as
		/// the comparison between elements.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also
		///   `true`. (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// This example shows how to use the `min(by:)` method on a
		/// dictionary to find the key-value pair with the lowest value.
		///
		///     let hues = ["Heliotrope": 296, "Coral": 16, "Aquamarine": 156]
		///     let leastHue = hues.min { a, b in a.value < b.value }
		///     print(leastHue)
		///     // Prints "Optional(("Coral", 16))"
		///
		/// - Parameter areInIncreasingOrder: A predicate that returns `true`
		///   if its first argument should be ordered before its second
		///   argument; otherwise, `false`.
		/// - Returns: The sequence's minimum element, according to
		///   `areInIncreasingOrder`. If the sequence has no elements, returns
		///   `nil`.
		///
		/// - SeeAlso: `min()`
		@warn_unqualified_access
		public func min(by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Element?
		
		/// Returns the maximum element in the sequence, using the given predicate
		/// as the comparison between elements.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also
		///   `true`. (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// This example shows how to use the `max(by:)` method on a
		/// dictionary to find the key-value pair with the highest value.
		///
		///     let hues = ["Heliotrope": 296, "Coral": 16, "Aquamarine": 156]
		///     let greatestHue = hues.max { a, b in a.value < b.value }
		///     print(greatestHue)
		///     // Prints "Optional(("Heliotrope", 296))"
		///
		/// - Parameter areInIncreasingOrder:  A predicate that returns `true` if its
		///   first argument should be ordered before its second argument;
		///   otherwise, `false`.
		/// - Returns: The sequence's maximum element if the sequence is not empty;
		///   otherwise, `nil`.
		///
		/// - SeeAlso: `max()`
		@warn_unqualified_access
		public func max(by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Element?
		
		/// Returns a Boolean value indicating whether the initial elements of the
		/// sequence are equivalent to the elements in another sequence, using
		/// the given predicate as the equivalence test.
		///
		/// The predicate must be a *equivalence relation* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areEquivalent(a, a)` is always `true`. (Reflexivity)
		/// - `areEquivalent(a, b)` implies `areEquivalent(b, a)`. (Symmetry)
		/// - If `areEquivalent(a, b)` and `areEquivalent(b, c)` are both `true`, then
		///   `areEquivalent(a, c)` is also `true`. (Transitivity)
		///
		/// - Parameters:
		///   - possiblePrefix: A sequence to compare to this sequence.
		///   - areEquivalent: A predicate that returns `true` if its two arguments
		///     are equivalent; otherwise, `false`.
		/// - Returns: `true` if the initial elements of the sequence are equivalent
		///   to the elements of `possiblePrefix`; otherwise, `false`. If
		///   `possiblePrefix` has no elements, the return value is `true`.
		///
		/// - SeeAlso: `starts(with:)`
		public func starts<PossiblePrefix where PossiblePrefix : Sequence, PossiblePrefix.Iterator.Element == Element>(with possiblePrefix: PossiblePrefix, by areEquivalent: (Element, Element) throws -> Bool) rethrows -> Bool
		
		/// Returns a Boolean value indicating whether this sequence and another
		/// sequence contain equivalent elements, using the given predicate as the
		/// equivalence test.
		///
		/// At least one of the sequences must be finite.
		///
		/// The predicate must be a *equivalence relation* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areEquivalent(a, a)` is always `true`. (Reflexivity)
		/// - `areEquivalent(a, b)` implies `areEquivalent(b, a)`. (Symmetry)
		/// - If `areEquivalent(a, b)` and `areEquivalent(b, c)` are both `true`, then
		///   `areEquivalent(a, c)` is also `true`. (Transitivity)
		///
		/// - Parameters:
		///   - other: A sequence to compare to this sequence.
		///   - areEquivalent: A predicate that returns `true` if its two arguments
		///     are equivalent; otherwise, `false`.
		/// - Returns: `true` if this sequence and `other` contain equivalent items,
		///   using `areEquivalent` as the equivalence test; otherwise, `false.`
		///
		/// - SeeAlso: `elementsEqual(_:)`
		public func elementsEqual<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence, by areEquivalent: (Element, Element) throws -> Bool) rethrows -> Bool
		
		/// Returns a Boolean value indicating whether the sequence precedes another
		/// sequence in a lexicographical (dictionary) ordering, using the given
		/// predicate to compare elements.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also
		///   `true`. (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// - Parameters:
		///   - other: A sequence to compare to this sequence.
		///   - areInIncreasingOrder:  A predicate that returns `true` if its first
		///     argument should be ordered before its second argument; otherwise,
		///     `false`.
		/// - Returns: `true` if this sequence precedes `other` in a dictionary
		///   ordering as ordered by `areInIncreasingOrder`; otherwise, `false`.
		///
		/// - Note: This method implements the mathematical notion of lexicographical
		///   ordering, which has no connection to Unicode.  If you are sorting
		///   strings to present to the end user, use `String` APIs that perform
		///   localized comparison instead.
		/// - SeeAlso: `lexicographicallyPrecedes(_:)`
		public func lexicographicallyPrecedes<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence, by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Bool
		
		/// Returns a Boolean value indicating whether the sequence contains an
		/// element that satisfies the given predicate.
		///
		/// You can use the predicate to check for an element of a type that
		/// doesn't conform to the `Equatable` protocol, such as the
		/// `HTTPResponse` enumeration in this example.
		///
		///     enum HTTPResponse {
		///         case ok
		///         case error(Int)
		///     }
		///
		///     let lastThreeResponses: [HTTPResponse] = [.ok, .ok, .error(404)]
		///     let hadError = lastThreeResponses.contains { element in
		///         if case .error = element {
		///             return true
		///         } else {
		///             return false
		///         }
		///     }
		///     // 'hadError' == true
		///
		/// Alternatively, a predicate can be satisfied by a range of `Equatable`
		/// elements or a general condition. This example shows how you can check an
		/// array for an expense greater than $100.
		///
		///     let expenses = [21.37, 55.21, 9.32, 10.18, 388.77, 11.41]
		///     let hasBigPurchase = expenses.contains { $0 > 100 }
		///     // 'hasBigPurchase' == true
		///
		/// - Parameter predicate: A closure that takes an element of the sequence
		///   as its argument and returns a Boolean value that indicates whether
		///   the passed element represents a match.
		/// - Returns: `true` if the sequence contains an element that satisfies
		///   `predicate`; otherwise, `false`.
		public func contains(where predicate: (Element) throws -> Bool) rethrows -> Bool
		
		/// Returns the result of calling the given combining closure with each
		/// element of this sequence and an accumulating value.
		///
		/// The `nextPartialResult` closure is called sequentially with an
		/// accumulating value initialized to `initialResult` and each
		/// element of the sequence. This example shows how to find the sum
		/// of an array of numbers.
		///
		///     let numbers = [1, 2, 3, 4]
		///     let addTwo: (Int, Int) -> Int = { x, y in x + y }
		///     let numberSum = numbers.reduce(0, addTwo)
		///     // 'numberSum' == 10
		///
		/// When `numbers.reduce(_:_:)` is called, the
		/// following steps occur:
		///
		/// 1. The `nextPartialResult` closure is called with the initial
		///    result and the first element of `numbers`, returning the sum:
		///    `1`.
		/// 2. The closure is called again repeatedly with the previous call's
		///    return value and each element of the sequence.
		/// 3. When the sequence is exhausted, the last value returned from the
		///    closure is returned to the caller.
		///
		/// - Parameters:
		///   - initialResult: the initial accumulating value.
		///   - nextPartialResult: A closure that combines an accumulating
		///     value and an element of the sequence into a new accumulating
		///     value, to be used in the next call of the
		///     `nextPartialResult` closure or returned to the caller.
		/// - Returns: The final accumulated value.
		public func reduce<Result>(_ initialResult: Result, _ nextPartialResult: (Result, Element) throws -> Result) rethrows -> Result
		
		/// Returns an array containing the concatenated results of calling the
		/// given transformation with each element of this sequence.
		///
		/// Use this method to receive a single-level collection when your
		/// transformation produces a sequence or collection for each element.
		///
		/// In this example, note the difference in the result of using `map` and
		/// `flatMap` with a transformation that returns an array.
		///
		///     let numbers = [1, 2, 3, 4]
		///
		///     let mapped = numbers.map { Array(count: $0, repeatedValue: $0) }
		///     // [[1], [2, 2], [3, 3, 3], [4, 4, 4, 4]]
		///
		///     let flatMapped = numbers.flatMap { Array(count: $0, repeatedValue: $0) }
		///     // [1, 2, 2, 3, 3, 3, 4, 4, 4, 4]
		///
		/// In fact, `s.flatMap(transform)`  is equivalent to
		/// `Array(s.map(transform).joined())`.
		///
		/// - Parameter transform: A closure that accepts an element of this
		///   sequence as its argument and returns a sequence or collection.
		/// - Returns: The resulting flattened array.
		///
		/// - Complexity: O(*m* + *n*), where *m* is the length of this sequence
		///   and *n* is the length of the result.
		/// - SeeAlso: `joined()`, `map(_:)`
		public func flatMap<SegmentOfResult : Sequence>(_ transform: (Element) throws -> SegmentOfResult) rethrows -> [SegmentOfResult.Iterator.Element]
		
		/// Returns an array containing the non-`nil` results of calling the given
		/// transformation with each element of this sequence.
		///
		/// Use this method to receive an array of nonoptional values when your
		/// transformation produces an optional value.
		///
		/// In this example, note the difference in the result of using `map` and
		/// `flatMap` with a transformation that returns an optional `Int` value.
		///
		///     let possibleNumbers = ["1", "2", "three", "///4///", "5"]
		///
		///     let mapped: [Int?] = numbers.map { str in Int(str) }
		///     // [1, 2, nil, nil, 5]
		///
		///     let flatMapped: [Int] = numbers.flatMap { str in Int(str) }
		///     // [1, 2, 5]
		///
		/// - Parameter transform: A closure that accepts an element of this
		///   sequence as its argument and returns an optional value.
		/// - Returns: An array of the non-`nil` results of calling `transform`
		///   with each element of the sequence.
		///
		/// - Complexity: O(*m* + *n*), where *m* is the length of this sequence
		///   and *n* is the length of the result.
		public func flatMap<ElementOfResult>(_ transform: (Element) throws -> ElementOfResult?) rethrows -> [ElementOfResult]
	}
	
	/// Supply the default `makeIterator()` method for `Collection` models
	/// that accept the default associated `Iterator`,
	/// `IndexingIterator<Self>`.
	extension ArraySlice {
		
		/// Returns an iterator over the elements of the collection.
		public func makeIterator() -> IndexingIterator<ArraySlice<Element>>
	}
	
	/// Default implementations of core requirements
	extension ArraySlice {
		
		/// A Boolean value indicating whether the collection is empty.
		///
		/// When you need to check whether your collection is empty, use the
		/// `isEmpty` property instead of checking that the `count` property is
		/// equal to zero. For collections that don't conform to
		/// `RandomAccessCollection`, accessing the `count` property iterates
		/// through the elements of the collection.
		///
		///     let horseName = "Silver"
		///     if horseName.characters.isEmpty {
		///         print("I've been through the desert on a horse with no name.")
		///     } else {
		///         print("Hi ho, \(horseName)!")
		///     }
		///     // Prints "Hi ho, Silver!")
		///
		/// - Complexity: O(1)
		public var isEmpty: Bool { get }
		
		/// The first element of the collection.
		///
		/// If the collection is empty, the value of this property is `nil`.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     if let firstNumber = numbers.first {
		///         print(firstNumber)
		///     }
		///     // Prints "10"
		public var first: Element? { get }
		
		/// A value less than or equal to the number of elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the length
		///   of the collection.
		public var underestimatedCount: Int { get }
		
		/// The number of elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the length
		///   of the collection.
		public var count: Int { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension ArraySlice {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyBidirectionalCollection<ArraySlice<Element>> { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension ArraySlice {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyCollection<ArraySlice<Element>> { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension ArraySlice {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyRandomAccessCollection<ArraySlice<Element>> { get }
	}
	
	/// Default implementation for forward collections.
	extension ArraySlice {
		
		/// Offsets the given index by the specified distance.
		///
		/// The value passed as `n` must not offset `i` beyond the `endIndex` or
		/// before the `startIndex` of this collection.
		///
		/// - Parameters:
		///   - i: A valid index of the collection.
		///   - n: The distance to offset `i`. `n` must not be negative unless the
		///     collection conforms to the `BidirectionalCollection` protocol.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the absolute
		///   value of `n`.
		public func formIndex(_ i: inout Int, offsetBy n: Int)
		
		/// Offsets the given index by the specified distance, or so that it equals
		/// the given limiting index.
		///
		/// The value passed as `n` must not offset `i` beyond the `endIndex` or
		/// before the `startIndex` of this collection, unless the index passed as
		/// `limit` prevents offsetting beyond those bounds.
		///
		/// - Parameters:
		///   - i: A valid index of the collection.
		///   - n: The distance to offset `i`. `n` must not be negative unless the
		///     collection conforms to the `BidirectionalCollection` protocol.
		/// - Returns: `true` if `i` has been offset by exactly `n` steps without
		///   going beyond `limit`; otherwise, `false`. When the return value is
		///   `false`, the value of `i` is equal to `limit`.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the absolute
		///   value of `n`.
		public func formIndex(_ i: inout Int, offsetBy n: Int, limitedBy limit: Int) -> Bool
	}
	
	extension ArraySlice : CustomReflectable {
		
		/// A mirror that reflects the array.
		public var customMirror: Mirror { get }
	}
	
	extension ArraySlice : RangeReplaceableCollection {
		
		/// Creates a new, empty array.
		///
		/// This is equivalent to initializing with an empty array literal.
		/// For example:
		///
		///     var emptyArray = Array<Int>()
		///     print(emptyArray.isEmpty)
		///     // Prints "true"
		///
		///     emptyArray = []
		///     print(emptyArray.isEmpty)
		///     // Prints "true"
		public init()
		
		/// Creates an array containing the elements of a sequence.
		///
		/// You can use this initializer to create an array from any other type that
		/// conforms to the `Sequence` protocol. For example, you might want to
		/// create an array with the integers from 1 through 7. Use this initializer
		/// around a range instead of typing all those numbers in an array literal.
		///
		///     let numbers = Array(1...7)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 6, 7]"
		///
		/// You can also use this initializer to convert a complex sequence or
		/// collection type back to an array. For example, the `keys` property of
		/// a dictionary isn't an array with its own storage, it's a collection
		/// that maps its elements from the dictionary only when they're
		/// accessed, saving the time and space needed to allocate an array. If
		/// you need to pass those keys to a method that takes an array, however,
		/// use this initializer to convert that list from its type of
		/// `LazyMapCollection<Dictionary<String, Int>, Int>` to a simple
		/// `[String]`.
		///
		///     func cacheImagesWithNames(names: [String]) {
		///         // custom image loading and caching
		///      }
		///
		///     let namedHues: [String: Int] = ["Vermillion": 18, "Magenta": 302,
		///             "Gold": 50, "Cerise": 320]
		///     let colorNames = Array(namedHues.keys)
		///     cacheImagesWithNames(colorNames)
		///
		///     print(colorNames)
		///     // Prints "["Gold", "Cerise", "Magenta", "Vermillion"]"
		///
		/// - Parameter s: The sequence of elements to turn into an array.
		public init<S : Sequence where S.Iterator.Element == Element>(_ s: S)
		
		/// Creates a new array containing the specified number of a single, repeated
		/// value.
		///
		/// Here's an example of creating an array initialized with five strings
		/// containing the letter *Z*.
		///
		///     let fiveZs = Array(repeating: "Z", count: 5)
		///     print(fiveZs)
		///     // Prints "["Z", "Z", "Z", "Z", "Z"]"
		///
		/// - Parameters:
		///   - repeatedValue: The element to repeat.
		///   - count: The number of times to repeat the value passed in the
		///     `repeating` parameter. `count` must be zero or greater.
		public init(repeating repeatedValue: Element, count: Int)
		
		/// The number of elements in the array.
		public var count: Int { get }
		
		/// The total number of elements that the array can contain using its current
		/// storage.
		///
		/// If the array grows larger than its capacity, it discards its current
		/// storage and allocates a larger one.
		///
		/// The following example creates an array of integers from an array literal,
		/// then appends the elements of another collection. Before appending, the
		/// array allocates new storage that is large enough store the resulting
		/// elements.
		///
		///     var numbers = [10, 20, 30, 40, 50]
		///     print("Count: \(numbers.count), capacity: \(numbers.capacity)")
		///     // Prints "Count: 5, capacity: 5"
		///
		///     numbers.append(contentsOf: stride(from: 60, through: 100, by: 10))
		///     print("Count: \(numbers.count), capacity: \(numbers.capacity)")
		///     // Prints "Count: 10, capacity: 12"
		public var capacity: Int { get }
		
		/// Reserves enough space to store the specified number of elements.
		///
		/// If you are adding a known number of elements to an array, use this method
		/// to avoid multiple reallocations. This method ensures that the array has
		/// unique, mutable, contiguous storage, with space allocated for at least
		/// the requested number of elements.
		///
		/// For performance reasons, the newly allocated storage may be larger than
		/// the requested capacity. Use the array's `capacity` property to determine
		/// the size of the new storage.
		///
		/// - Parameter minimumCapacity: The requested number of elements to store.
		///
		/// - Complexity: O(*n*), where *n* is the count of the array.
		public mutating func reserveCapacity(_ minimumCapacity: Int)
		
		/// Adds a new element at the end of the array.
		///
		/// Use this method to append a single element to the end of a mutable array.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(100)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 100]"
		///
		/// Because arrays increase their allocated capacity using an exponential
		/// strategy, appending a single element to an array is an O(1) operation
		/// when averaged over many calls to the `append(_:)` method. When an array
		/// has additional capacity and is not sharing its storage with another
		/// instance, appending an element is O(1). When an array needs to
		/// reallocate storage before appending or its storage is shared with
		/// another copy, appending is O(*n*), where *n* is the length of the array.
		///
		/// - Parameter newElement: The element to append to the array.
		///
		/// - Complexity: Amortized O(1) over many additions. If the array uses a
		///   bridged `NSArray` instance as its storage, the efficiency is
		///   unspecified.
		public mutating func append(_ newElement: Element)
		
		/// Adds the elements of a sequence to the end of the array.
		///
		/// Use this method to append the elements of a sequence to the end of an
		/// array. This example appends the elements of a `Range<Int>` instance
		/// to an array of integers.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(contentsOf: 10...15)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
		///
		/// - Parameter newElements: The elements to append to the array.
		///
		/// - Complexity: O(*n*), where *n* is the length of the resulting array.
		public mutating func append<S : Sequence where S.Iterator.Element == Element>(contentsOf newElements: S)
		
		/// Adds the elements of a collection to the end of the array.
		///
		/// Use this method to append the elements of a collection to the end of this
		/// array. This example appends the elements of a `Range<Int>` instance
		/// to an array of integers.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(contentsOf: 10...15)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
		///
		/// - Parameter newElements: The elements to append to the array.
		///
		/// - Complexity: O(*n*), where *n* is the length of the resulting array.
		public mutating func append<C : Collection where C.Iterator.Element == Element>(contentsOf newElements: C)
		
		/// Inserts a new element at the specified position.
		///
		/// The new element is inserted before the element currently at the specified
		/// index. If you pass the array's `endIndex` property as the `index`
		/// parameter, the new element is appended to the array.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.insert(100, at: 3)
		///     numbers.insert(200, at: numbers.endIndex)
		///
		///     print(numbers)
		///     // Prints "[1, 2, 3, 100, 4, 5, 200]"
		///
		/// - Parameter newElement: The new element to insert into the array.
		/// - Parameter i: The position at which to insert the new element.
		///   `index` must be a valid index of the array or equal to its `endIndex`
		///   property.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func insert(_ newElement: Element, at i: Int)
		
		/// Removes and returns the element at the specified position.
		///
		/// All the elements following the specified position are moved up to
		/// close the gap.
		///
		///     var measurements: [Double] = [1.1, 1.5, 2.9, 1.2, 1.5, 1.3, 1.2]
		///     let removed = measurements.remove(at: 2)
		///     print(measurements)
		///     // Prints "[1.1, 1.5, 1.2, 1.5, 1.3, 1.2]"
		///
		/// - Parameter index: The position of the element to remove. `index` must
		///   be a valid index of the array.
		/// - Returns: The element at the specified index.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func remove(at index: Int) -> Element
		
		/// Removes all elements from the array.
		///
		/// - Parameter keepCapacity: Pass `true` to keep the existing capacity of
		///   the array after removing its elements. The default value is
		///   `false`.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func removeAll(keepingCapacity keepCapacity: Bool = default)
	}
	
	extension ArraySlice : ExpressibleByArrayLiteral {
		
		/// Creates an array from the given array literal.
		///
		/// Do not call this initializer directly. It is used by the compiler when
		/// you use an array literal. Instead, create a new array by using an array
		/// literal as its value. To do this, enclose a comma-separated list of
		/// values in square brackets.
		///
		/// Here, an array of strings is created from an array literal holding only
		/// strings:
		///
		///     let ingredients: ArraySlice =
		///           ["cocoa beans", "sugar", "cocoa butter", "salt"]
		///
		/// - Parameter elements: A variadic list of elements of the new array.
		public init(arrayLiteral elements: Element...)
	}
	
	extension ArraySlice : CustomStringConvertible, CustomDebugStringConvertible {
		
		/// A textual representation of the array and its elements.
		public var description: String { get }
		
		/// A textual representation of the array and its elements, suitable for
		/// debugging.
		public var debugDescription: String { get }
	}
	
	extension ArraySlice where Element : Equatable {
		
		/// Returns the longest possible subsequences of the collection, in order,
		/// around elements equal to the given element.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the collection are not returned as part
		/// of any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string at each
		/// space character (" "). The first use of `split` returns each word that
		/// was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(separator: " ")
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(line.characters.split(separator: " ", maxSplits: 1)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(separator: " ", omittingEmptySubsequences: false)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - separator: The element that should be split upon.
		///   - maxSplits: The maximum number of times to split the collection, or
		///     one less than the number of subsequences to return. If
		///     `maxSplits + 1` subsequences are returned, the last one is a suffix
		///     of the original collection containing the remaining elements.
		///     `maxSplits` must be greater than or equal to zero. The default value
		///     is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each consecutive pair of `separator`
		///     elements in the collection and for each instance of `separator` at
		///     the start or end of the collection. If `true`, only nonempty
		///     subsequences are returned. The default value is `true`.
		/// - Returns: An array of subsequences, split from this collection's
		///   elements.
		public func split(separator: Element, maxSplits: Int = default, omittingEmptySubsequences: Bool = default) -> [ArraySlice<Element>]
		
		/// Returns the first index where the specified value appears in the
		/// collection.
		///
		/// After using `index(of:)` to find the position of a particular element in
		/// a collection, you can use it to access the element by subscripting. This
		/// example shows how you can modify one of the names in an array of
		/// students.
		///
		///     var students = ["Ben", "Ivy", "Jordell", "Maxime"]
		///     if let i = students.index(of: "Maxime") {
		///         students[i] = "Max"
		///     }
		///     print(students)
		///     // Prints "["Ben", "Ivy", "Jordell", "Max"]"
		///
		/// - Parameter element: An element to search for in the collection.
		/// - Returns: The first index where `element` is found. If `element` is not
		///   found in the collection, returns `nil`.
		///
		/// - SeeAlso: `index(where:)`
		public func index(of element: Element) -> Int?
		
		/// Returns the longest possible subsequences of the sequence, in order,
		/// around elements equal to the given element.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the sequence are not returned as part of
		/// any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string at each
		/// space character (" "). The first use of `split` returns each word that
		/// was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(separator: " ")
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(line.characters.split(separator: " ", maxSplits: 1)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(separator: " ", omittingEmptySubsequences: false)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - separator: The element that should be split upon.
		///   - maxSplits: The maximum number of times to split the sequence, or one
		///     less than the number of subsequences to return. If `maxSplits + 1`
		///     subsequences are returned, the last one is a suffix of the original
		///     sequence containing the remaining elements. `maxSplits` must be
		///     greater than or equal to zero. The default value is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each consecutive pair of `separator`
		///     elements in the sequence and for each instance of `separator` at the
		///     start or end of the sequence. If `true`, only nonempty subsequences
		///     are returned. The default value is `true`.
		/// - Returns: An array of subsequences, split from this sequence's elements.
		public func split(separator: Element, maxSplits: Int = default, omittingEmptySubsequences: Bool = default) -> [AnySequence<Element>]
		
		/// Returns a Boolean value indicating whether the initial elements of the
		/// sequence are the same as the elements in another sequence.
		///
		/// This example tests whether one countable range begins with the elements
		/// of another countable range.
		///
		///     let a = 1...3
		///     let b = 1...10
		///
		///     print(b.starts(with: a))
		///     // Prints "true"
		///
		/// Passing an sequence with no elements or an empty collection as
		/// `possiblePrefix` always results in `true`.
		///
		///     print(b.starts(with: []))
		///     // Prints "true"
		///
		/// - Parameter possiblePrefix: A sequence to compare to this sequence.
		/// - Returns: `true` if the initial elements of the sequence are the same as
		///   the elements of `possiblePrefix`; otherwise, `false`. If
		///   `possiblePrefix` has no elements, the return value is `true`.
		///
		/// - SeeAlso: `starts(with:by:)`
		public func starts<PossiblePrefix where PossiblePrefix : Sequence, PossiblePrefix.Iterator.Element == Element>(with possiblePrefix: PossiblePrefix) -> Bool
		
		/// Returns a Boolean value indicating whether this sequence and another
		/// sequence contain the same elements in the same order.
		///
		/// At least one of the sequences must be finite.
		///
		/// This example tests whether one countable range shares the same elements
		/// as another countable range and an array.
		///
		///     let a = 1...3
		///     let b = 1...10
		///
		///     print(a.elementsEqual(b))
		///     // Prints "false"
		///     print(a.elementsEqual([1, 2, 3]))
		///     // Prints "true"
		///
		/// - Parameter other: A sequence to compare to this sequence.
		/// - Returns: `true` if this sequence and `other` contain the same elements
		///   in the same order.
		///
		/// - SeeAlso: `elementsEqual(_:by:)`
		public func elementsEqual<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence) -> Bool
	}
	
	extension ArraySlice where Element == String {
		
		/// Returns a new string by concatenating the elements of the sequence,
		/// adding the given separator between each element.
		///
		/// The following example shows how an array of strings can be joined to a
		/// single, comma-separated string:
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let list = cast.joined(separator: ", ")
		///     print(list)
		///     // Prints "Vivien, Marlon, Kim, Karl"
		///
		/// - Parameter separator: A string to insert between each of the elements
		///   in this sequence. The default separator is an empty string.
		/// - Returns: A single, concatenated string.
		public func joined(separator: String = default) -> String
	}
	
	extension ArraySlice where Element : Collection {
		
		/// Returns the elements of this collection of collections, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   collection of collections.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenCollection<ArraySlice<Element>>
	}
	
	extension ArraySlice where Element : BidirectionalCollection {
		
		/// Returns the elements of this collection of collections, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   collection of collections.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenBidirectionalCollection<ArraySlice<Element>>
	}
	
	extension ArraySlice where Element : Sequence {
		
		/// Returns the elements of this sequence of sequences, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   sequence of sequences.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenSequence<ArraySlice<Element>>
		
		/// Returns the concatenated elements of this sequence of sequences,
		/// inserting the given separator between each element.
		///
		/// This example shows how an array of `[Int]` instances can be joined, using
		/// another `[Int]` instance as the separator:
		///
		///     let nestedNumbers = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
		///     let joined = nestedNumbers.joined(separator: [-1, -2])
		///     print(Array(joined))
		///     // Prints "[1, 2, 3, -1, -2, 4, 5, 6, -1, -2, 7, 8, 9]"
		///
		/// - Parameter separator: A sequence to insert between each of this
		///   sequence's elements.
		/// - Returns: The joined sequence of elements.
		///
		/// - SeeAlso: `joined()`
		public func joined<Separator : Sequence where Separator.Iterator.Element == Iterator.Element.Iterator.Element>(separator: Separator) -> JoinedSequence<ArraySlice<Element>>
	}
	
	extension ArraySlice where Element : Comparable {
		
		/// Returns the elements of the sequence, sorted.
		///
		/// You can sort any sequence of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let sortedStudents = students.sorted()
		///     print(sortedStudents)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your sequence in descending order, pass the
		/// greater-than operator (`>`) to the `sorted(by:)` method.
		///
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Returns: A sorted array of the sequence's elements.
		///
		/// - SeeAlso: `sorted(by:)`
		///
		public func sorted() -> [Element]
		
		/// Returns the elements of the collection, sorted.
		///
		/// You can sort any collection of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let sortedStudents = students.sorted()
		///     print(sortedStudents)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your collection in descending order, pass the
		/// greater-than operator (`>`) to the `sorted(by:)` method.
		///
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Returns: A sorted array of the collection's elements.
		///
		/// - SeeAlso: `sorted(by:)`
		/// - MutatingVariant: sort
		public func sorted() -> [Element]
		
		/// Sorts the collection in place.
		///
		/// You can sort any mutable collection of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     var students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     students.sort()
		///     print(students)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your collection in descending order, pass the
		/// greater-than operator (`>`) to the `sort(by:)` method.
		///
		///     students.sort(by: >)
		///     print(students)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		public mutating func sort()
		
		/// Returns the minimum element in the sequence.
		///
		/// This example finds the smallest value in an array of height measurements.
		///
		///     let heights = [67.5, 65.7, 64.3, 61.1, 58.5, 60.3, 64.9]
		///     let lowestHeight = heights.min()
		///     print(lowestHeight)
		///     // Prints "Optional(58.5)"
		///
		/// - Returns: The sequence's minimum element. If the sequence has no
		///   elements, returns `nil`.
		///
		/// - SeeAlso: `min(by:)`
		@warn_unqualified_access
		public func min() -> Element?
		
		/// Returns the maximum element in the sequence.
		///
		/// This example finds the smallest value in an array of height measurements.
		///
		///     let heights = [67.5, 65.7, 64.3, 61.1, 58.5, 60.3, 64.9]
		///     let greatestHeight = heights.max()
		///     print(greatestHeight)
		///     // Prints "Optional(67.5)"
		///
		/// - Returns: The sequence's maximum element. If the sequence has no
		///   elements, returns `nil`.
		///
		/// - SeeAlso: `max(by:)`
		@warn_unqualified_access
		public func max() -> Element?
		
		/// Returns a Boolean value indicating whether the sequence precedes another
		/// sequence in a lexicographical (dictionary) ordering, using the
		/// less-than operator (`<`) to compare elements.
		///
		/// This example uses the `lexicographicallyPrecedes` method to test which
		/// array of integers comes first in a lexicographical ordering.
		///
		///     let a = [1, 2, 2, 2]
		///     let b = [1, 2, 3, 4]
		///
		///     print(a.lexicographicallyPrecedes(b))
		///     // Prints "true"
		///     print(b.lexicographicallyPrecedes(b))
		///     // Prints "false"
		///
		/// - Parameter other: A sequence to compare to this sequence.
		/// - Returns: `true` if this sequence precedes `other` in a dictionary
		///   ordering; otherwise, `false`.
		///
		/// - Note: This method implements the mathematical notion of lexicographical
		///   ordering, which has no connection to Unicode.  If you are sorting
		///   strings to present to the end user, use `String` APIs that
		///   perform localized comparison.
		/// - SeeAlso: `lexicographicallyPrecedes(_:by:)`
		public func lexicographicallyPrecedes<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence) -> Bool
	}
	
	/// An ordered, random-access collection.
	///
	/// Arrays are one of the most commonly used data types in an app. You use
	/// arrays to organize your app's data. Specifically, you use the `Array` type
	/// to hold elements of a single type, the array's `Element` type. An array
	/// can store any kind of elements---from integers to strings to classes.
	///
	/// Swift makes it easy to create arrays in your code using an array literal:
	/// simply surround a comma separated list of values with square brackets.
	/// Without any other information, Swift creates an array that includes the
	/// specified values, automatically inferring the array's `Element` type. For
	/// example:
	///
	///     // An array of 'Int' elements
	///     let oddNumbers = [1, 3, 5, 7, 9, 11, 13, 15]
	///
	///     // An array of 'String' elements
	///     let streets = ["Albemarle", "Brandywine", "Chesapeake"]
	///
	/// You can create an empty array by specifying the `Element` type of your
	/// array in the declaration. For example:
	///
	///     // Shortened forms are preferred
	///     var emptyDoubles: [Double] = []
	///
	///     // The full type name is also allowed
	///     var emptyFloats: Array<Float> = Array()
	///
	/// If you need an array that is preinitialized with a fixed number of default
	/// values, use the `Array(repeating:count:)` initializer.
	///
	///     var digitCounts = Array(repeating: 0, count: 10)
	///     print(digitCounts)
	///     // Prints "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]"
	///
	/// Accessing Array Values
	/// ======================
	///
	/// When you need to perform an operation on all of an array's elements, use a
	/// `for`-`in` loop to iterate through the array's contents.
	///
	///     for street in streets {
	///         print("I don't live on \(street).")
	///     }
	///     // Prints "I don't live on Albemarle."
	///     // Prints "I don't live on Brandywine."
	///     // Prints "I don't live on Chesapeake."
	///
	/// Use the `isEmpty` property to check quickly whether an array has any
	/// elements, or use the `count` property to find the number of elements in
	/// the array.
	///
	///     if oddNumbers.isEmpty {
	///         print("I don't know any odd numbers.")
	///     } else {
	///         print("I know \(oddNumbers.count) odd numbers.")
	///     }
	///     // Prints "I know 8 odd numbers."
	///
	/// Use the `first` and `last` properties for safe access to the value of the
	/// array's first and last elements. If the array is empty, these properties
	/// are `nil`.
	///
	///     if let firstElement = oddNumbers.first, let lastElement = oddNumbers.last {
	///         print(firstElement, lastElement, separator: ", ")
	///     }
	///     // Prints "1, 15"
	///
	///     print(emptyDoubles.first, emptyDoubles.last, separator: ", ")
	///     // Prints "nil, nil"
	///
	/// You can access individual array elements through a subscript. The first
	/// element of a nonempty array is always at index zero. You can subscript an
	/// array with any integer from zero up to, but not including, the count of
	/// the array. Using a negative number or an index equal to or greater than
	/// `count` triggers a runtime error. For example:
	///
	///     print(oddNumbers[0], oddNumbers[3], separator: ", ")
	///     // Prints "1, 7"
	///
	///     print(emptyDoubles[0])
	///     // Triggers runtime error: Index out of range
	///
	/// See the `Sequence`, `Collection`, and `RangeReplaceableCollection`
	/// protocols for more methods available to arrays.
	///
	/// Adding and Removing Elements
	/// ============================
	///
	/// Suppose you need to store a list of the names of students that are signed
	/// up for a class you're teaching. During the registration period, you need
	/// to add and remove names as students add and drop the class.
	///
	///     var students = ["Ben", "Ivy", "Jordell"]
	///
	/// To add single elements to the end of an array, use the `append(_:)` method.
	/// Add multiple elements at the same time by passing another array or a
	/// sequence of any kind to the `append(contentsOf:)` method.
	///
	///     students.append("Maxime")
	///     students.append(contentsOf: ["Shakia", "William"])
	///     // ["Ben", "Ivy", "Jordell", "Maxime", "Shakia", "William"]
	///
	/// You can add new elements in the middle of an array by using the
	/// `insert(_:at:)` method for single elements and by using
	/// `insert(contentsOf:at:)` to insert multiple elements from another
	/// collection or array literal. The elements at that index and later indices
	/// are shifted back to make room.
	///
	///     students.insert("Liam", at: 3)
	///     // ["Ben", "Ivy", "Jordell", "Liam", "Maxime", "Shakia", "William"]
	///
	/// To remove elements from an array, use the `remove(at:)`,
	/// `removeSubrange(_:)`, and `removeLast()` methods.
	///
	///     // Ben's family is moving to another state
	///     students.remove(at: 0)
	///     // ["Ivy", "Jordell", "Liam", "Maxime", "Shakia", "William"]
	///
	///     // William is signing up for a different class
	///     students.removeLast()
	///     // ["Ivy", "Jordell", "Liam", "Maxime", "Shakia"]
	///
	/// You can replace an existing element with a new value by assigning the new
	/// value to the subscript.
	///
	///     if let i = students.index(of: "Maxime") {
	///         students[i] = "Max"
	///     }
	///     // ["Ivy", "Jordell", "Liam", "Max", "Shakia"]
	///
	/// Growing the Size of an Array
	/// ----------------------------
	///
	/// Every array reserves a specific amount of memory to hold its contents. When
	/// you add elements to an array and that array begins to exceed its reserved
	/// capacity, the array allocates a larger region of memory and copies its
	/// elements into the new storage. The new storage is a multiple of the old
	/// storage's size. This exponential growth strategy means that appending an
	/// element happens in constant time, averaging the performance of many append
	/// operations. Append operations that trigger reallocation have a performance
	/// cost, but they occur less and less often as the array grows larger.
	///
	/// If you know approximately how many elements you will need to store, use the
	/// `reserveCapacity(_:)` method before appending to the array to avoid
	/// intermediate reallocations. Use the `capacity` and `count` properties to
	/// determine how many more elements the array can store without allocating
	/// larger storage.
	///
	/// For arrays of most `Element` types, this storage is a contiguous block of
	/// memory. For arrays with an `Element` type that is a class or `@objc`
	/// protocol type, this storage can be a contiguous block of memory or an
	/// instance of `NSArray`. Because any arbitrary subclass of `NSArray` can
	/// become an `Array`, there are no guarantees about representation or
	/// efficiency in this case.
	///
	/// Modifying Copies of Arrays
	/// ==========================
	///
	/// Each array has an independent value that includes the values of all of its
	/// elements. For simple types such as integers and other structures, this
	/// means that when you change a value in one array, the value of that element
	/// does not change in any copies of the array. For example:
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     var numbersCopy = numbers
	///     numbers[0] = 100
	///     print(numbers)
	///     // Prints "[100, 2, 3, 4, 5]"
	///     print(numbersCopy)
	///     // Prints "[1, 2, 3, 4, 5]"
	///
	/// If the elements in an array are instances of a class, the semantics are the
	/// same, though they might appear different at first. In this case, the
	/// values stored in the array are references to objects that live outside the
	/// array. If you change a reference to an object in one array, only that
	/// array has a reference to the new object. However, if two arrays contain
	/// references to the same object, you can observe changes to that object's
	/// properties from both arrays. For example:
	///
	///     // An integer type with reference semantics
	///     class IntegerReference {
	///         var value = 10
	///     }
	///     var firstIntegers = [IntegerReference(), IntegerReference()]
	///     var secondIntegers = firstIntegers
	///
	///     // Modifications to an instance are visible from either array
	///     firstIntegers[0].value = 100
	///     print(secondIntegers[0].value)
	///     // Prints "100"
	///
	///     // Replacements, additions, and removals are still visible
	///     // only in the modified array
	///     firstIntegers[0] = IntegerReference()
	///     print(firstIntegers[0].value)
	///     // Prints "10"
	///     print(secondIntegers[0].value)
	///     // Prints "100"
	///
	/// Arrays, like all variable-size collections in the standard library, use
	/// copy-on-write optimization. Multiple copies of an array share the same
	/// storage until you modify one of the copies. When that happens, the array
	/// being modified replaces its storage with a uniquely owned copy of itself,
	/// which is then modified in place. Optimizations are sometimes applied that
	/// can reduce the amount of copying.
	///
	/// This means that if an array is sharing storage with other copies, the first
	/// mutating operation on that array incurs the cost of copying the array. An
	/// array that is the sole owner of its storage can perform mutating
	/// operations in place.
	///
	/// In the example below, a `numbers` array is created along with two copies
	/// that share the same storage. When the original `numbers` array is
	/// modified, it makes a unique copy of its storage before making the
	/// modification. Further modifications to `numbers` are made in place, while
	/// the two copies continue to share the original storage.
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     var firstCopy = numbers
	///     var secondCopy = numbers
	///
	///     // The storage for 'numbers' is copied here
	///     numbers[0] = 100
	///     numbers[1] = 200
	///     numbers[2] = 300
	///     // 'numbers' is [100, 200, 300, 4, 5]
	///     // 'firstCopy' and 'secondCopy' are [1, 2, 3, 4, 5]
	///
	/// Bridging Between Array and NSArray
	/// ==================================
	///
	/// When you need to access APIs that expect data in an `NSArray` instance
	/// instead of `Array`, use the type-cast operator (`as`) to bridge your
	/// instance. For bridging to be possible, the `Element` type of your array
	/// must be a class, an `@objc` protocol (a protocol imported from Objective-C
	/// or marked with the `@objc` attribute), or a type that bridges to a
	/// Foundation type.
	///
	/// The following example shows how you can bridge an `Array` instance to
	/// `NSArray` to use the `write(to:atomically:)` method. In this example, the
	/// `colors` array can be bridged to `NSArray` because its `String` elements
	/// bridge to `NSString`. The compiler prevents bridging the `moreColors`
	/// array, on the other hand, because its `Element` type is
	/// `Optional<String>`, which does *not* bridge to a Foundation type.
	///
	///     let colors = ["periwinkle", "rose", "moss"]
	///     let moreColors: [String?] = ["ochre", "pine"]
	///
	///     let url = NSURL(fileURLWithPath: "names.plist")
	///     (colors as NSArray).write(to: url, atomically: true)
	///     // true
	///
	///     (moreColors as NSArray).write(to: url, atomically: true)
	///     // error: cannot convert value of type '[String?]' to type 'NSArray'
	///
	/// Bridging from `Array` to `NSArray` takes O(1) time and O(1) space if the
	/// array's elements are already instances of a class or an `@objc` protocol;
	/// otherwise, it takes O(*n*) time and space.
	///
	/// Bridging from `NSArray` to `Array` first calls the `copy(with:)`
	/// (`- copyWithZone:` in Objective-C) method on the array to get an immutable
	/// copy and then performs additional Swift bookkeeping work that takes O(1)
	/// time. For instances of `NSArray` that are already immutable, `copy(with:)`
	/// usually returns the same array in O(1) time; otherwise, the copying
	/// performance is unspecified. The instances of `NSArray` and `Array` share
	/// storage using the same copy-on-write optimization that is used when two
	/// instances of `Array` share storage.
	///
	/// - Note: The `ContiguousArray` and `ArraySlice` types are not bridged;
	///   instances of those types always have a contiguous block of memory as
	///   their storage.
	/// - SeeAlso: `ContiguousArray`, `ArraySlice`, `Sequence`, `Collection`,
	///   `RangeReplaceableCollection`
	public struct Array<Element> : RandomAccessCollection, MutableCollection {
		
		/// A type that represents a position in the collection.
		///
		/// Valid indices consist of the position of every element and a
		/// "past the end" position that's not valid for use as a subscript
		/// argument.
		///
		/// - SeeAlso: endIndex
		public typealias Index = Int
		
		/// A type that provides the collection's iteration interface and
		/// encapsulates its iteration state.
		///
		/// By default, a collection conforms to the `Sequence` protocol by
		/// supplying a `IndexingIterator` as its associated `Iterator`
		/// type.
		public typealias Iterator = IndexingIterator<[Element]>
		
		/// The position of the first element in a nonempty array.
		///
		/// For an instance of `Array`, `startIndex` is always zero. If the array
		/// is empty, `startIndex` is equal to `endIndex`.
		public var startIndex: Int { get }
		
		/// The array's "past the end" position---that is, the position one greater
		/// than the last valid subscript argument.
		///
		/// When you need a range that includes the last element of an array, use the
		/// half-open range operator (`..<`) with `endIndex`. The `..<` operator
		/// creates a range that doesn't include the upper bound, so it's always
		/// safe to use with `endIndex`. For example:
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     if let i = numbers.index(of: 30) {
		///         print(numbers[i ..< numbers.endIndex])
		///     }
		///     // Prints "[30, 40, 50]"
		///
		/// If the array is empty, `endIndex` is equal to `startIndex`.
		public var endIndex: Int { get }
		
		/// Returns the position immediately after the given index.
		///
		/// - Parameter i: A valid index of the collection. `i` must be less than
		///   `endIndex`.
		/// - Returns: The index value immediately after `i`.
		public func index(after i: Int) -> Int
		
		/// Replaces the given index with its successor.
		///
		/// - Parameter i: A valid index of the collection. `i` must be less than
		///   `endIndex`.
		public func formIndex(after i: inout Int)
		
		/// Returns the position immediately before the given index.
		///
		/// - Parameter i: A valid index of the collection. `i` must be greater than
		///   `startIndex`.
		/// - Returns: The index value immediately before `i`.
		public func index(before i: Int) -> Int
		
		/// Replaces the given index with its predecessor.
		///
		/// - Parameter i: A valid index of the collection. `i` must be greater than
		///   `startIndex`.
		public func formIndex(before i: inout Int)
		
		/// Returns an index that is the specified distance from the given index.
		///
		/// The following example obtains an index advanced four positions from an
		/// array's starting index and then prints the element at that position.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     let i = numbers.index(numbers.startIndex, offsetBy: 4)
		///     print(numbers[i])
		///     // Prints "50"
		///
		/// Advancing an index beyond a collection's ending index or offsetting it
		/// before a collection's starting index may trigger a runtime error. The
		/// value passed as `n` must not result in such an operation.
		///
		/// - Parameters:
		///   - i: A valid index of the array.
		///   - n: The distance to offset `i`.
		/// - Returns: An index offset by `n` from the index `i`. If `n` is positive,
		///   this is the same value as the result of `n` calls to `index(after:)`.
		///   If `n` is negative, this is the same value as the result of `-n` calls
		///   to `index(before:)`.
		///
		/// - Complexity: O(1)
		public func index(_ i: Int, offsetBy n: Int) -> Int
		
		/// Returns an index that is the specified distance from the given index,
		/// unless that distance is beyond a given limiting index.
		///
		/// The following example obtains an index advanced four positions from an
		/// array's starting index and then prints the element at that position. The
		/// operation doesn't require going beyond the limiting `numbers.endIndex`
		/// value, so it succeeds.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     let i = numbers.index(numbers.startIndex,
		///                           offsetBy: 4,
		///                           limitedBy: numbers.endIndex)
		///     print(numbers[i])
		///     // Prints "50"
		///
		/// The next example attempts to retrieve an index ten positions from
		/// `numbers.startIndex`, but fails, because that distance is beyond the
		/// index passed as `limit`.
		///
		///     let j = numbers.index(numbers.startIndex,
		///                           offsetBy: 10,
		///                           limitedBy: numbers.endIndex)
		///     print(j)
		///     // Prints "nil"
		///
		/// Advancing an index beyond a collection's ending index or offsetting it
		/// before a collection's starting index may trigger a runtime error. The
		/// value passed as `n` must not result in such an operation.
		///
		/// - Parameters:
		///   - i: A valid index of the array.
		///   - n: The distance to offset `i`.
		///   - limit: A valid index of the collection to use as a limit. If `n > 0`,
		///     `limit` has no effect if it is less than `i`. Likewise, if `n < 0`,
		///     `limit` has no effect if it is greater than `i`.
		/// - Returns: An index offset by `n` from the index `i`, unless that index
		///   would be beyond `limit` in the direction of movement. In that case,
		///   the method returns `nil`.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1)
		public func index(_ i: Int, offsetBy n: Int, limitedBy limit: Int) -> Int?
		
		/// Returns the distance between two indices.
		///
		/// - Parameters:
		///   - start: A valid index of the collection.
		///   - end: Another valid index of the collection. If `end` is equal to
		///     `start`, the result is zero.
		/// - Returns: The distance between `start` and `end`.
		public func distance(from start: Int, to end: Int) -> Int
		
		/// A type that can represent the indices that are valid for subscripting the
		/// collection, in ascending order.
		public typealias Indices = CountableRange<Int>
		
		/// Accesses the element at the specified position.
		///
		/// The following example uses indexed subscripting to update an array's
		/// second element. After assigning the new value (`"Butler"`) at a specific
		/// position, that value is immediately available at that same position.
		///
		///     var streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     streets[1] = "Butler"
		///     print(streets[1])
		///     // Prints "Butler"
		///
		/// - Parameter index: The position of the element to access. `index` must be
		///   greater than or equal to `startIndex` and less than `endIndex`.
		///
		/// - Complexity: Reading an element from an array is O(1). Writing is O(1)
		///   unless the array's storage is shared with another array, in which case
		///   writing is O(*n*), where *n* is the length of the array.
		///   If the array uses a bridged `NSArray` instance as its storage, the
		///   efficiency is unspecified.
		public subscript(index: Int) -> Element
		
		/// Accesses a contiguous subrange of the array's elements.
		///
		/// The returned `ArraySlice` instance uses the same indices for the same
		/// elements as the original array. In particular, that slice, unlike an
		/// array, may have a nonzero `startIndex` and an `endIndex` that is not
		/// equal to `count`. Always use the slice's `startIndex` and `endIndex`
		/// properties instead of assuming that its indices start or end at a
		/// particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let i = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[i!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of integers. The bounds of the range must be
		///   valid indices of the array.
		///
		/// - SeeAlso: `ArraySlice`
		public subscript(bounds: Range<Int>) -> ArraySlice<Element>
		
		/// Calls a closure with a pointer to the array's contiguous storage.
		///  If no such storage exists, it is first created.
		///
		/// Often, the optimizer can eliminate bounds checks within an array
		/// algorithm, but when that fails, invoking the same algorithm on the
		/// buffer pointer passed into your closure lets you trade safety for speed.
		///
		/// The following example shows how you can iterate over the contents of the
		/// buffer pointer:
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     let sum = numbers.withUnsafeBufferPointer { buffer -> Int in
		///         var result = 0
		///         for i in stride(from: buffer.startIndex, to: buffer.endIndex, by: 2) {
		///             result += buffer[i]
		///         }
		///         return result
		///     }
		///     // 'sum' == 9
		///
		/// - Parameter body: A closure with an `UnsafeBufferPointer` parameter that
		///   points to the contiguous storage for the array. If `body` has a return
		///   value, it is used as the return value for the
		///   `withUnsafeBufferPointer(_:)` method. The pointer argument is valid
		///   only for the duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeMutableBufferPointer`, `UnsafeBufferPointer`
		public func withUnsafeBufferPointer<R>(_ body: (UnsafeBufferPointer<Element>) throws -> R) rethrows -> R
		
		/// Calls the given closure with a pointer to the array's mutable contiguous
		/// storage. If no such storage exists, it is first created.
		///
		/// Often, the optimizer can eliminate bounds checks within an array
		/// algorithm, but when that fails, invoking the same algorithm on the
		/// buffer pointer passed into your closure lets you trade safety for speed.
		///
		/// The following example shows modifying the contents of the
		/// `UnsafeMutableBufferPointer` argument to `body` alters the contents of
		/// the array:
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.withUnsafeMutableBufferPointer { buffer in
		///         for i in stride(from: buffer.startIndex, to: buffer.endIndex - 1, by: 2) {
		///             swap(&buffer[i], &buffer[i + 1])
		///         }
		///     }
		///     print(numbers)
		///     // Prints "[2, 1, 4, 3, 5]"
		///
		/// - Warning: Do not rely on anything about `self` (the array that is the
		///   target of this method) during the execution of the `body` closure: It
		///   may not appear to have its correct value.  Instead, use only the
		///   `UnsafeMutableBufferPointer` argument to `body`.
		///
		/// - Parameter body: A closure with an `UnsafeMutableBufferPointer`
		///   parameter that points to the contiguous storage for the array. If
		///   `body` has a return value, it is used as the return value for the
		///   `withUnsafeMutableBufferPointer(_:)` method. The pointer argument is
		///   valid only for the duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeBufferPointer`, `UnsafeMutableBufferPointer`
		public mutating func withUnsafeMutableBufferPointer<R>(_ body: (inout UnsafeMutableBufferPointer<Element>) throws -> R) rethrows -> R
		
		/// Replaces a range of elements with the elements in the specified
		/// collection.
		///
		/// This method has the effect of removing the specified range of elements
		/// from the array and inserting the new elements at the same location. The
		/// number of new elements need not match the number of elements being
		/// removed.
		///
		/// In this example, three elements in the middle of an array of integers are
		/// replaced by the five elements of a `Repeated<Int>` instance.
		///
		///      var nums = [10, 20, 30, 40, 50]
		///      nums.replaceSubrange(1...3, with: repeatElement(1, count: 5))
		///      print(nums)
		///      // Prints "[10, 1, 1, 1, 1, 1, 50]"
		///
		/// If you pass a zero-length range as the `subrange` parameter, this method
		/// inserts the elements of `newElements` at `subrange.startIndex`. Calling
		/// the `insert(contentsOf:at:)` method instead is preferred.
		///
		/// Likewise, if you pass a zero-length collection as the `newElements`
		/// parameter, this method removes the elements in the given subrange
		/// without replacement. Calling the `removeSubrange(_:)` method instead is
		/// preferred.
		///
		/// - Parameters:
		///   - subrange: The subrange of the array to replace. The start and end of
		///     a subrange must be valid indices of the array.
		///   - newElements: The new elements to add to the array.
		///
		/// - Complexity: O(`subrange.count`) if you are replacing a suffix of the
		///   array with an empty collection; otherwise, O(*n*), where *n* is the
		///   length of the array.
		public mutating func replaceSubrange<C where C : Collection, C.Iterator.Element == _Buffer.Element>(_ subrange: Range<Int>, with newElements: C)
		
		/// Calls a closure with a view of the array's underlying bytes of memory as a
		/// Collection of `UInt8`.
		///
		///  If no such storage exists, it is first created.
		///
		/// - Precondition: `Pointee` is a trivial type.
		///
		/// The following example shows how you copy bytes into an array:
		///
		///    var numbers = [Int32](repeating: 0, count: 2)
		///    var byteValues: [UInt8] = [0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00]
		///    numbers.withUnsafeMutableBytes { destBytes in
		///      byteValues.withUnsafeBytes { srcBytes in
		///        destBytes.copyBytes(from: srcBytes)
		///      }
		///    }
		///
		/// - Parameter body: A closure with an `UnsafeRawBufferPointer`
		///   parameter that points to the contiguous storage for the array. If `body`
		///   has a return value, it is used as the return value for the
		///   `withUnsafeMutableBytes(_:)` method. The argument is valid only for the
		///   duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeBytes`, `UnsafeMutableRawBufferPointer`
		public mutating func withUnsafeMutableBytes<R>(_ body: (UnsafeMutableRawBufferPointer) throws -> R) rethrows -> R
		
		/// Calls a closure with a view of the array's underlying bytes of memory
		/// as a Collection of `UInt8`.
		///
		///  If no such storage exists, it is first created.
		///
		/// - Precondition: `Pointee` is a trivial type.
		///
		/// The following example shows how you copy the contents of an array into a
		/// buffer of `UInt8`:
		///
		///    let numbers = [1, 2, 3]
		///    var byteBuffer = [UInt8]()
		///    numbers.withUnsafeBytes {
		///        byteBuffer += $0
		///    }
		///
		/// - Parameter body: A closure with an `UnsafeRawBufferPointer` parameter
		///   that points to the contiguous storage for the array. If `body` has a
		///   return value, it is used as the return value for the
		///   `withUnsafeBytes(_:)` method. The argument is valid only for the
		///   duration of the closure's execution.
		/// - Returns: The return value of the `body` closure parameter, if any.
		///
		/// - SeeAlso: `withUnsafeBytes`, `UnsafeRawBufferPointer`
		public func withUnsafeBytes<R>(_ body: (UnsafeRawBufferPointer) throws -> R) rethrows -> R
		
		/// Removes and returns the last element of the array.
		///
		/// - Returns: The last element of the array if the array is not empty;
		///   otherwise, `nil`.
		///
		/// - Complexity: O(*n*) if the array is bridged, where *n* is the length
		///   of the array; otherwise, O(1).
		/// - SeeAlso: `removeLast()`
		public mutating func popLast() -> Element?
		
		/// Returns a subsequence containing all but the specified number of final
		/// elements.
		///
		/// If the number of elements to drop exceeds the number of elements in the
		/// collection, the result is an empty subsequence.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropLast(2))
		///     // Prints "[1, 2, 3]"
		///     print(numbers.dropLast(10))
		///     // Prints "[]"
		///
		/// - Parameter n: The number of elements to drop off the end of the
		///   collection. `n` must be greater than or equal to zero.
		/// - Returns: A subsequence that leaves off `n` elements from the end.
		///
		/// - Complexity: O(*n*), where *n* is the number of elements to drop.
		public func dropLast(_ n: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence, up to the given maximum length, containing the
		/// final elements of the collection.
		///
		/// If the maximum length exceeds the number of elements in the collection,
		/// the result contains the entire collection.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.suffix(2))
		///     // Prints "[4, 5]"
		///     print(numbers.suffix(10))
		///     // Prints "[1, 2, 3, 4, 5]"
		///
		/// - Parameter maxLength: The maximum number of elements to return.
		///   `maxLength` must be greater than or equal to zero.
		/// - Returns: A subsequence terminating at the end of the collection with at
		///   most `maxLength` elements.
		///
		/// - Complexity: O(*n*), where *n* is equal to `maxLength`.
		public func suffix(_ maxLength: Int) -> ArraySlice<Element>
		
		/// Returns an array containing the results of mapping the given closure
		/// over the sequence's elements.
		///
		/// In this example, `map` is used first to convert the names in the array
		/// to lowercase strings and then to count their characters.
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let lowercaseNames = cast.map { $0.lowercaseString }
		///     // 'lowercaseNames' == ["vivien", "marlon", "kim", "karl"]
		///     let letterCounts = cast.map { $0.characters.count }
		///     // 'letterCounts' == [6, 6, 3, 4]
		///
		/// - Parameter transform: A mapping closure. `transform` accepts an
		///   element of this sequence as its parameter and returns a transformed
		///   value of the same or of a different type.
		/// - Returns: An array containing the transformed elements of this
		///   sequence.
		public func map<T>(_ transform: (Element) throws -> T) rethrows -> [T]
		
		/// Returns a subsequence containing all but the given number of initial
		/// elements.
		///
		/// If the number of elements to drop exceeds the number of elements in
		/// the collection, the result is an empty subsequence.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropFirst(2))
		///     // Prints "[3, 4, 5]"
		///     print(numbers.dropFirst(10))
		///     // Prints "[]"
		///
		/// - Parameter n: The number of elements to drop from the beginning of
		///   the collection. `n` must be greater than or equal to zero.
		/// - Returns: A subsequence starting after the specified number of
		///   elements.
		///
		/// - Complexity: O(*n*), where *n* is the number of elements to drop from
		///   the beginning of the collection.
		public func dropFirst(_ n: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence, up to the specified maximum length, containing
		/// the initial elements of the collection.
		///
		/// If the maximum length exceeds the number of elements in the collection,
		/// the result contains all the elements in the collection.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.prefix(2))
		///     // Prints "[1, 2]"
		///     print(numbers.prefix(10))
		///     // Prints "[1, 2, 3, 4, 5]"
		///
		/// - Parameter maxLength: The maximum number of elements to return.
		///   `maxLength` must be greater than or equal to zero.
		/// - Returns: A subsequence starting at the beginning of this collection
		///   with at most `maxLength` elements.
		public func prefix(_ maxLength: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence from the start of the collection up to, but not
		/// including, the specified position.
		///
		/// The resulting subsequence *does not include* the element at the position
		/// `end`. The following example searches for the index of the number `40`
		/// in an array of integers, and then prints the prefix of the array up to,
		/// but not including, that index:
		///
		///     let numbers = [10, 20, 30, 40, 50, 60]
		///     if let i = numbers.index(of: 40) {
		///         print(numbers.prefix(upTo: i))
		///     }
		///     // Prints "[10, 20, 30]"
		///
		/// Passing the collection's starting index as the `end` parameter results in
		/// an empty subsequence.
		///
		///     print(numbers.prefix(upTo: numbers.startIndex))
		///     // Prints "[]"
		///
		/// - Parameter end: The "past the end" index of the resulting subsequence.
		///   `end` must be a valid index of the collection.
		/// - Returns: A subsequence up to, but not including, the `end` position.
		///
		/// - Complexity: O(1)
		/// - SeeAlso: `prefix(through:)`
		public func prefix(upTo end: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence from the specified position to the end of the
		/// collection.
		///
		/// The following example searches for the index of the number `40` in an
		/// array of integers, and then prints the suffix of the array starting at
		/// that index:
		///
		///     let numbers = [10, 20, 30, 40, 50, 60]
		///     if let i = numbers.index(of: 40) {
		///         print(numbers.suffix(from: i))
		///     }
		///     // Prints "[40, 50, 60]"
		///
		/// Passing the collection's `endIndex` as the `start` parameter results in
		/// an empty subsequence.
		///
		///     print(numbers.suffix(from: numbers.endIndex))
		///     // Prints "[]"
		///
		/// - Parameter start: The index at which to start the resulting subsequence.
		///   `start` must be a valid index of the collection.
		/// - Returns: A subsequence starting at the `start` position.
		///
		/// - Complexity: O(1)
		public func suffix(from start: Int) -> ArraySlice<Element>
		
		/// Returns a subsequence from the start of the collection through the
		/// specified position.
		///
		/// The resulting subsequence *includes* the element at the position `end`.
		/// The following example searches for the index of the number `40` in an
		/// array of integers, and then prints the prefix of the array up to, and
		/// including, that index:
		///
		///     let numbers = [10, 20, 30, 40, 50, 60]
		///     if let i = numbers.index(of: 40) {
		///         print(numbers.prefix(through: i))
		///     }
		///     // Prints "[10, 20, 30, 40]"
		///
		/// - Parameter end: The index of the last element to include in the
		///   resulting subsequence. `end` must be a valid index of the collection
		///   that is not equal to the `endIndex` property.
		/// - Returns: A subsequence up to, and including, the `end` position.
		///
		/// - Complexity: O(1)
		/// - SeeAlso: `prefix(upTo:)`
		public func prefix(through position: Int) -> ArraySlice<Element>
		
		/// Returns the longest possible subsequences of the collection, in order,
		/// that don't contain elements satisfying the given predicate.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the sequence are not returned as part of
		/// any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string using a
		/// closure that matches spaces. The first use of `split` returns each word
		/// that was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(whereSeparator: { $0 == " " })
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(
		///         line.characters.split(
		///             maxSplits: 1, whereSeparator: { $0 == " " }
		///             ).map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(omittingEmptySubsequences: false, whereSeparator: { $0 == " " })
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - maxSplits: The maximum number of times to split the collection, or
		///     one less than the number of subsequences to return. If
		///     `maxSplits + 1` subsequences are returned, the last one is a suffix
		///     of the original collection containing the remaining elements.
		///     `maxSplits` must be greater than or equal to zero. The default value
		///     is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each pair of consecutive elements
		///     satisfying the `isSeparator` predicate and for each element at the
		///     start or end of the collection satisfying the `isSeparator`
		///     predicate. The default value is `true`.
		///   - isSeparator: A closure that takes an element as an argument and
		///     returns a Boolean value indicating whether the collection should be
		///     split at that element.
		/// - Returns: An array of subsequences, split from this collection's
		///   elements.
		public func split(maxSplits: Int = default, omittingEmptySubsequences: Bool = default, whereSeparator isSeparator: (Element) throws -> Bool) rethrows -> [ArraySlice<Element>]
		
		/// The last element of the collection.
		///
		/// If the collection is empty, the value of this property is `nil`.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     if let lastNumber = numbers.last {
		///         print(lastNumber)
		///     }
		///     // Prints "50"
		public var last: Element? { get }
		
		/// Returns the first index in which an element of the collection satisfies
		/// the given predicate.
		///
		/// You can use the predicate to find an element of a type that doesn't
		/// conform to the `Equatable` protocol or to find an element that matches
		/// particular criteria. Here's an example that finds a student name that
		/// begins with the letter "A":
		///
		///     let students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     if let i = students.index(where: { $0.hasPrefix("A") }) {
		///         print("\(students[i]) starts with 'A'!")
		///     }
		///     // Prints "Abena starts with 'A'!"
		///
		/// - Parameter predicate: A closure that takes an element as its argument
		///   and returns a Boolean value that indicates whether the passed element
		///   represents a match.
		/// - Returns: The index of the first element for which `predicate` returns
		///   `true`. If no elements in the collection satisfy the given predicate,
		///   returns `nil`.
		///
		/// - SeeAlso: `index(of:)`
		public func index(where predicate: (Element) throws -> Bool) rethrows -> Int?
		
		public mutating func partition(by belongsInSecondPartition: (Element) throws -> Bool) rethrows -> Int
		
		public mutating func partition(by belongsInSecondPartition: (Element) throws -> Bool) rethrows -> Int
		
		/// Returns the elements of the collection, sorted using the given
		/// predicate as the comparison between elements.
		///
		/// When you want to sort a collection of elements that don't conform to
		/// the `Comparable` protocol, pass a predicate to this method that returns
		/// `true` when the first element passed should be ordered before the
		/// second. The elements of the resulting array are ordered according to the
		/// given predicate.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also `true`.
		///   (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements for which `areInIncreasingOrder` does not
		/// establish an order.
		///
		/// In the following example, the predicate provides an ordering for an array
		/// of a custom `HTTPResponse` type. The predicate orders errors before
		/// successes and sorts the error responses by their error code.
		///
		///     enum HTTPResponse {
		///         case ok
		///         case error(Int)
		///     }
		///
		///     let responses: [HTTPResponse] = [.error(500), .ok, .ok, .error(404), .error(403)]
		///     let sortedResponses = responses.sorted {
		///         switch ($0, $1) {
		///         // Order errors by code
		///         case let (.error(aCode), .error(bCode)):
		///             return aCode < bCode
		///
		///         // All successes are equivalent, so none is before any other
		///         case (.ok, .ok): return false
		///
		///         // Order errors before successes
		///         case (.error, .ok): return true
		///         case (.ok, .error): return false
		///         }
		///     }
		///     print(sortedResponses)
		///     // Prints "[.error(403), .error(404), .error(500), .ok, .ok]"
		///
		/// You also use this method to sort elements that conform to the
		/// `Comparable` protocol in descending order. To sort your collection
		/// in descending order, pass the greater-than operator (`>`) as the
		/// `areInIncreasingOrder` parameter.
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// Calling the related `sorted()` method is equivalent to calling this
		/// method and passing the less-than operator (`<`) as the predicate.
		///
		///     print(students.sorted())
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///     print(students.sorted(by: <))
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// - Parameter areInIncreasingOrder: A predicate that returns `true` if its first
		///   argument should be ordered before its second argument; otherwise,
		///   `false`.
		/// - Returns: A sorted array of the collection's elements.
		///
		/// - SeeAlso: `sorted()`
		/// - MutatingVariant: sort
		public func sorted(by areInIncreasingOrder: (Element, Element) -> Bool) -> [Element]
		
		/// Sorts the collection in place, using the given predicate as the
		/// comparison between elements.
		///
		/// When you want to sort a collection of elements that doesn't conform to
		/// the `Comparable` protocol, pass a closure to this method that returns
		/// `true` when the first element passed should be ordered before the
		/// second.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also `true`.
		///   (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements for which `areInIncreasingOrder` does not
		/// establish an order.
		///
		/// In the following example, the closure provides an ordering for an array
		/// of a custom enumeration that describes an HTTP response. The predicate
		/// orders errors before successes and sorts the error responses by their
		/// error code.
		///
		///     enum HTTPResponse {
		///         case ok
		///         case error(Int)
		///     }
		///
		///     var responses: [HTTPResponse] = [.error(500), .ok, .ok, .error(404), .error(403)]
		///     responses.sort {
		///         switch ($0, $1) {
		///         // Order errors by code
		///         case let (.error(aCode), .error(bCode)):
		///             return aCode < bCode
		///
		///         // All successes are equivalent, so none is before any other
		///         case (.ok, .ok): return false
		///
		///         // Order errors before successes
		///         case (.error, .ok): return true
		///         case (.ok, .error): return false
		///         }
		///     }
		///     print(responses)
		///     // Prints "[.error(403), .error(404), .error(500), .ok, .ok]"
		///
		/// Alternatively, use this method to sort a collection of elements that do
		/// conform to `Comparable` when you want the sort to be descending instead
		/// of ascending. Pass the greater-than operator (`>`) operator as the
		/// predicate.
		///
		///     var students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     students.sort(by: >)
		///     print(students)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Parameter areInIncreasingOrder: A predicate that returns `true` if its first
		///   argument should be ordered before its second argument; otherwise,
		///   `false`.
		public mutating func sort(by areInIncreasingOrder: (Element, Element) -> Bool)
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[index!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: ClosedRange<Int>) -> ArraySlice<Element> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[index!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableRange<Int>) -> ArraySlice<Element> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     print(streets[index!])
		///     // Prints "Evarts"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableClosedRange<Int>) -> ArraySlice<Element> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: ClosedRange<Int>) -> ArraySlice<Element>
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableRange<Int>) -> ArraySlice<Element>
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: CountableClosedRange<Int>) -> ArraySlice<Element>
		
		/// A sequence containing the same elements as this sequence,
		/// but on which some operations, such as `map` and `filter`, are
		/// implemented lazily.
		///
		/// - SeeAlso: `LazySequenceProtocol`, `LazySequence`
		public var lazy: LazySequence<Array<Element>> { get }
		
		/// Accesses a contiguous subrange of the collection's elements.
		///
		/// The accessed slice uses the same indices for the same elements as the
		/// original collection. Always use the slice's `startIndex` property
		/// instead of assuming that its indices start at a particular value.
		///
		/// This example demonstrates getting a slice of an array of strings, finding
		/// the index of one of the strings in the slice, and then using that index
		/// in the original array.
		///
		///     let streets = ["Adams", "Bryant", "Channing", "Douglas", "Evarts"]
		///     let streetsSlice = streets[2 ..< streets.endIndex]
		///     print(streetsSlice)
		///     // Prints "["Channing", "Douglas", "Evarts"]"
		///
		///     let index = streetsSlice.index(of: "Evarts")    // 4
		///     streets[index!] = "Eustace"
		///     print(streets[index!])
		///     // Prints "Eustace"
		///
		/// - Parameter bounds: A range of the collection's indices. The bounds of
		///   the range must be valid indices of the collection.
		public subscript(bounds: Range<Int>) -> MutableSlice<Array<Element>>
		
		/// The indices that are valid for subscripting the collection, in ascending
		/// order.
		///
		/// A collection's `indices` property can hold a strong reference to the
		/// collection itself, causing the collection to be non-uniquely referenced.
		/// If you mutate the collection while iterating over its indices, a strong
		/// reference can cause an unexpected copy of the collection. To avoid the
		/// unexpected copy, use the `index(after:)` method starting with
		/// `startIndex` to produce indices instead.
		///
		///     var c = MyFancyCollection([10, 20, 30, 40, 50])
		///     var i = c.startIndex
		///     while i != c.endIndex {
		///         c[i] /= 5
		///         i = c.index(after: i)
		///     }
		///     // c == MyFancyCollection([2, 4, 6, 8, 10])
		public var indices: CountableRange<Int> { get }
		
		/// Returns a view presenting the elements of the collection in reverse
		/// order.
		///
		/// You can reverse a collection without allocating new space for its
		/// elements by calling this `reversed()` method. A
		/// `ReversedRandomAccessCollection` instance wraps an underlying collection
		/// and provides access to its elements in reverse order. This example
		/// prints the elements of an array in reverse order:
		///
		///     let numbers = [3, 5, 7]
		///     for number in numbers.reversed() {
		///         print(number)
		///     }
		///     // Prints "7"
		///     // Prints "5"
		///     // Prints "3"
		///
		/// If you need a reversed collection of the same type, you may be able to
		/// use the collection's sequence-based or collection-based initializer. For
		/// example, to get the reversed version of an array, initialize a new
		/// `Array` instance from the result of this `reversed()` method.
		///
		///     let reversedNumbers = Array(numbers.reversed())
		///     print(reversedNumbers)
		///     // Prints "[7, 5, 3]"
		///
		/// - Complexity: O(1)
		public func reversed() -> ReversedRandomAccessCollection<Array<Element>>
		
		/// Returns an array containing the results of mapping the given closure
		/// over the sequence's elements.
		///
		/// In this example, `map` is used first to convert the names in the array
		/// to lowercase strings and then to count their characters.
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let lowercaseNames = cast.map { $0.lowercaseString }
		///     // 'lowercaseNames' == ["vivien", "marlon", "kim", "karl"]
		///     let letterCounts = cast.map { $0.characters.count }
		///     // 'letterCounts' == [6, 6, 3, 4]
		///
		/// - Parameter transform: A mapping closure. `transform` accepts an
		///   element of this sequence as its parameter and returns a transformed
		///   value of the same or of a different type.
		/// - Returns: An array containing the transformed elements of this
		///   sequence.
		public func map<T>(_ transform: (Element) throws -> T) rethrows -> [T]
		
		/// Returns an array containing, in order, the elements of the sequence
		/// that satisfy the given predicate.
		///
		/// In this example, `filter` is used to include only names shorter than
		/// five characters.
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let shortNames = cast.filter { $0.characters.count < 5 }
		///     print(shortNames)
		///     // Prints "["Kim", "Karl"]"
		///
		/// - Parameter shouldInclude: A closure that takes an element of the
		///   sequence as its argument and returns a Boolean value indicating
		///   whether the element should be included in the returned array.
		/// - Returns: An array of the elements that `includeElement` allowed.
		public func filter(_ isIncluded: (Element) throws -> Bool) rethrows -> [Element]
		
		/// Returns a value less than or equal to the number of elements in
		/// the sequence, nondestructively.
		///
		/// - Complexity: O(*n*)
		public var underestimatedCount: Int { get }
		
		/// Calls the given closure on each element in the sequence in the same order
		/// as a `for`-`in` loop.
		///
		/// The two loops in the following example produce the same output:
		///
		///     let numberWords = ["one", "two", "three"]
		///     for word in numberWords {
		///         print(word)
		///     }
		///     // Prints "one"
		///     // Prints "two"
		///     // Prints "three"
		///
		///     numberWords.forEach { word in
		///         print(word)
		///     }
		///     // Same as above
		///
		/// Using the `forEach` method is distinct from a `for`-`in` loop in two
		/// important ways:
		///
		/// 1. You cannot use a `break` or `continue` statement to exit the current
		///    call of the `body` closure or skip subsequent calls.
		/// 2. Using the `return` statement in the `body` closure will exit only from
		///    the current call to `body`, not from any outer scope, and won't skip
		///    subsequent calls.
		///
		/// - Parameter body: A closure that takes an element of the sequence as a
		///   parameter.
		public func forEach(_ body: (Element) throws -> Void) rethrows
		
		/// Returns the first element of the sequence that satisfies the given
		/// predicate or nil if no such element is found.
		///
		/// - Parameter predicate: A closure that takes an element of the
		///   sequence as its argument and returns a Boolean value indicating
		///   whether the element is a match.
		/// - Returns: The first match or `nil` if there was no match.
		public func first(where predicate: (Element) throws -> Bool) rethrows -> Element?
		
		/// Returns a subsequence containing all but the first element of the
		/// sequence.
		///
		/// The following example drops the first element from an array of integers.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropFirst())
		///     // Prints "[2, 3, 4, 5]"
		///
		/// If the sequence has no elements, the result is an empty subsequence.
		///
		///     let empty: [Int] = []
		///     print(empty.dropFirst())
		///     // Prints "[]"
		///
		/// - Returns: A subsequence starting after the first element of the
		///   sequence.
		///
		/// - Complexity: O(1)
		public func dropFirst() -> ArraySlice<Element>
		
		/// Returns a subsequence containing all but the last element of the
		/// sequence.
		///
		/// The sequence must be finite. If the sequence has no elements, the result
		/// is an empty subsequence.
		///
		///     let numbers = [1, 2, 3, 4, 5]
		///     print(numbers.dropLast())
		///     // Prints "[1, 2, 3, 4]"
		///
		/// If the sequence has no elements, the result is an empty subsequence.
		///
		///     let empty: [Int] = []
		///     print(empty.dropLast())
		///     // Prints "[]"
		///
		/// - Returns: A subsequence leaving off the last element of the sequence.
		///
		/// - Complexity: O(*n*), where *n* is the length of the sequence.
		public func dropLast() -> ArraySlice<Element>
		
		/// Returns a sequence of pairs (*n*, *x*), where *n* represents a
		/// consecutive integer starting at zero, and *x* represents an element of
		/// the sequence.
		///
		/// This example enumerates the characters of the string "Swift" and prints
		/// each character along with its place in the string.
		///
		///     for (n, c) in "Swift".characters.enumerated() {
		///         print("\(n): '\(c)'")
		///     }
		///     // Prints "0: 'S'"
		///     // Prints "1: 'w'"
		///     // Prints "2: 'i'"
		///     // Prints "3: 'f'"
		///     // Prints "4: 't'"
		///
		/// When enumerating a collection, the integer part of each pair is a counter
		/// for the enumeration, not necessarily the index of the paired value.
		/// These counters can only be used as indices in instances of zero-based,
		/// integer-indexed collections, such as `Array` and `ContiguousArray`. For
		/// other collections the counters may be out of range or of the wrong type
		/// to use as an index. To iterate over the elements of a collection with its
		/// indices, use the `zip(_:_:)` function.
		///
		/// This example iterates over the indices and elements of a set, building a
		/// list of indices of names with five or fewer letters.
		///
		///     let names: Set = ["Sofia", "Camilla", "Martina", "Mateo", "Nicolás"]
		///     var shorterIndices: [SetIndex<String>] = []
		///     for (i, name) in zip(names.indices, names) {
		///         if name.characters.count <= 5 {
		///             shorterIndices.append(i)
		///         }
		///     }
		///
		/// Now that the `shorterIndices` array holds the indices of the shorter
		/// names in the `names` set, you can use those indices to access elements in
		/// the set.
		///
		///     for i in shorterIndices {
		///         print(names[i])
		///     }
		///     // Prints "Sofia"
		///     // Prints "Mateo"
		///
		/// - Returns: A sequence of pairs enumerating the sequence.
		public func enumerated() -> EnumeratedSequence<Array<Element>>
		
		/// Returns the minimum element in the sequence, using the given predicate as
		/// the comparison between elements.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also
		///   `true`. (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// This example shows how to use the `min(by:)` method on a
		/// dictionary to find the key-value pair with the lowest value.
		///
		///     let hues = ["Heliotrope": 296, "Coral": 16, "Aquamarine": 156]
		///     let leastHue = hues.min { a, b in a.value < b.value }
		///     print(leastHue)
		///     // Prints "Optional(("Coral", 16))"
		///
		/// - Parameter areInIncreasingOrder: A predicate that returns `true`
		///   if its first argument should be ordered before its second
		///   argument; otherwise, `false`.
		/// - Returns: The sequence's minimum element, according to
		///   `areInIncreasingOrder`. If the sequence has no elements, returns
		///   `nil`.
		///
		/// - SeeAlso: `min()`
		@warn_unqualified_access
		public func min(by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Element?
		
		/// Returns the maximum element in the sequence, using the given predicate
		/// as the comparison between elements.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also
		///   `true`. (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// This example shows how to use the `max(by:)` method on a
		/// dictionary to find the key-value pair with the highest value.
		///
		///     let hues = ["Heliotrope": 296, "Coral": 16, "Aquamarine": 156]
		///     let greatestHue = hues.max { a, b in a.value < b.value }
		///     print(greatestHue)
		///     // Prints "Optional(("Heliotrope", 296))"
		///
		/// - Parameter areInIncreasingOrder:  A predicate that returns `true` if its
		///   first argument should be ordered before its second argument;
		///   otherwise, `false`.
		/// - Returns: The sequence's maximum element if the sequence is not empty;
		///   otherwise, `nil`.
		///
		/// - SeeAlso: `max()`
		@warn_unqualified_access
		public func max(by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Element?
		
		/// Returns a Boolean value indicating whether the initial elements of the
		/// sequence are equivalent to the elements in another sequence, using
		/// the given predicate as the equivalence test.
		///
		/// The predicate must be a *equivalence relation* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areEquivalent(a, a)` is always `true`. (Reflexivity)
		/// - `areEquivalent(a, b)` implies `areEquivalent(b, a)`. (Symmetry)
		/// - If `areEquivalent(a, b)` and `areEquivalent(b, c)` are both `true`, then
		///   `areEquivalent(a, c)` is also `true`. (Transitivity)
		///
		/// - Parameters:
		///   - possiblePrefix: A sequence to compare to this sequence.
		///   - areEquivalent: A predicate that returns `true` if its two arguments
		///     are equivalent; otherwise, `false`.
		/// - Returns: `true` if the initial elements of the sequence are equivalent
		///   to the elements of `possiblePrefix`; otherwise, `false`. If
		///   `possiblePrefix` has no elements, the return value is `true`.
		///
		/// - SeeAlso: `starts(with:)`
		public func starts<PossiblePrefix where PossiblePrefix : Sequence, PossiblePrefix.Iterator.Element == Element>(with possiblePrefix: PossiblePrefix, by areEquivalent: (Element, Element) throws -> Bool) rethrows -> Bool
		
		/// Returns a Boolean value indicating whether this sequence and another
		/// sequence contain equivalent elements, using the given predicate as the
		/// equivalence test.
		///
		/// At least one of the sequences must be finite.
		///
		/// The predicate must be a *equivalence relation* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areEquivalent(a, a)` is always `true`. (Reflexivity)
		/// - `areEquivalent(a, b)` implies `areEquivalent(b, a)`. (Symmetry)
		/// - If `areEquivalent(a, b)` and `areEquivalent(b, c)` are both `true`, then
		///   `areEquivalent(a, c)` is also `true`. (Transitivity)
		///
		/// - Parameters:
		///   - other: A sequence to compare to this sequence.
		///   - areEquivalent: A predicate that returns `true` if its two arguments
		///     are equivalent; otherwise, `false`.
		/// - Returns: `true` if this sequence and `other` contain equivalent items,
		///   using `areEquivalent` as the equivalence test; otherwise, `false.`
		///
		/// - SeeAlso: `elementsEqual(_:)`
		public func elementsEqual<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence, by areEquivalent: (Element, Element) throws -> Bool) rethrows -> Bool
		
		/// Returns a Boolean value indicating whether the sequence precedes another
		/// sequence in a lexicographical (dictionary) ordering, using the given
		/// predicate to compare elements.
		///
		/// The predicate must be a *strict weak ordering* over the elements. That
		/// is, for any elements `a`, `b`, and `c`, the following conditions must
		/// hold:
		///
		/// - `areInIncreasingOrder(a, a)` is always `false`. (Irreflexivity)
		/// - If `areInIncreasingOrder(a, b)` and `areInIncreasingOrder(b, c)` are
		///   both `true`, then `areInIncreasingOrder(a, c)` is also
		///   `true`. (Transitive comparability)
		/// - Two elements are *incomparable* if neither is ordered before the other
		///   according to the predicate. If `a` and `b` are incomparable, and `b`
		///   and `c` are incomparable, then `a` and `c` are also incomparable.
		///   (Transitive incomparability)
		///
		/// - Parameters:
		///   - other: A sequence to compare to this sequence.
		///   - areInIncreasingOrder:  A predicate that returns `true` if its first
		///     argument should be ordered before its second argument; otherwise,
		///     `false`.
		/// - Returns: `true` if this sequence precedes `other` in a dictionary
		///   ordering as ordered by `areInIncreasingOrder`; otherwise, `false`.
		///
		/// - Note: This method implements the mathematical notion of lexicographical
		///   ordering, which has no connection to Unicode.  If you are sorting
		///   strings to present to the end user, use `String` APIs that perform
		///   localized comparison instead.
		/// - SeeAlso: `lexicographicallyPrecedes(_:)`
		public func lexicographicallyPrecedes<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence, by areInIncreasingOrder: (Element, Element) throws -> Bool) rethrows -> Bool
		
		/// Returns a Boolean value indicating whether the sequence contains an
		/// element that satisfies the given predicate.
		///
		/// You can use the predicate to check for an element of a type that
		/// doesn't conform to the `Equatable` protocol, such as the
		/// `HTTPResponse` enumeration in this example.
		///
		///     enum HTTPResponse {
		///         case ok
		///         case error(Int)
		///     }
		///
		///     let lastThreeResponses: [HTTPResponse] = [.ok, .ok, .error(404)]
		///     let hadError = lastThreeResponses.contains { element in
		///         if case .error = element {
		///             return true
		///         } else {
		///             return false
		///         }
		///     }
		///     // 'hadError' == true
		///
		/// Alternatively, a predicate can be satisfied by a range of `Equatable`
		/// elements or a general condition. This example shows how you can check an
		/// array for an expense greater than $100.
		///
		///     let expenses = [21.37, 55.21, 9.32, 10.18, 388.77, 11.41]
		///     let hasBigPurchase = expenses.contains { $0 > 100 }
		///     // 'hasBigPurchase' == true
		///
		/// - Parameter predicate: A closure that takes an element of the sequence
		///   as its argument and returns a Boolean value that indicates whether
		///   the passed element represents a match.
		/// - Returns: `true` if the sequence contains an element that satisfies
		///   `predicate`; otherwise, `false`.
		public func contains(where predicate: (Element) throws -> Bool) rethrows -> Bool
		
		/// Returns the result of calling the given combining closure with each
		/// element of this sequence and an accumulating value.
		///
		/// The `nextPartialResult` closure is called sequentially with an
		/// accumulating value initialized to `initialResult` and each
		/// element of the sequence. This example shows how to find the sum
		/// of an array of numbers.
		///
		///     let numbers = [1, 2, 3, 4]
		///     let addTwo: (Int, Int) -> Int = { x, y in x + y }
		///     let numberSum = numbers.reduce(0, addTwo)
		///     // 'numberSum' == 10
		///
		/// When `numbers.reduce(_:_:)` is called, the
		/// following steps occur:
		///
		/// 1. The `nextPartialResult` closure is called with the initial
		///    result and the first element of `numbers`, returning the sum:
		///    `1`.
		/// 2. The closure is called again repeatedly with the previous call's
		///    return value and each element of the sequence.
		/// 3. When the sequence is exhausted, the last value returned from the
		///    closure is returned to the caller.
		///
		/// - Parameters:
		///   - initialResult: the initial accumulating value.
		///   - nextPartialResult: A closure that combines an accumulating
		///     value and an element of the sequence into a new accumulating
		///     value, to be used in the next call of the
		///     `nextPartialResult` closure or returned to the caller.
		/// - Returns: The final accumulated value.
		public func reduce<Result>(_ initialResult: Result, _ nextPartialResult: (Result, Element) throws -> Result) rethrows -> Result
		
		/// Returns an array containing the concatenated results of calling the
		/// given transformation with each element of this sequence.
		///
		/// Use this method to receive a single-level collection when your
		/// transformation produces a sequence or collection for each element.
		///
		/// In this example, note the difference in the result of using `map` and
		/// `flatMap` with a transformation that returns an array.
		///
		///     let numbers = [1, 2, 3, 4]
		///
		///     let mapped = numbers.map { Array(count: $0, repeatedValue: $0) }
		///     // [[1], [2, 2], [3, 3, 3], [4, 4, 4, 4]]
		///
		///     let flatMapped = numbers.flatMap { Array(count: $0, repeatedValue: $0) }
		///     // [1, 2, 2, 3, 3, 3, 4, 4, 4, 4]
		///
		/// In fact, `s.flatMap(transform)`  is equivalent to
		/// `Array(s.map(transform).joined())`.
		///
		/// - Parameter transform: A closure that accepts an element of this
		///   sequence as its argument and returns a sequence or collection.
		/// - Returns: The resulting flattened array.
		///
		/// - Complexity: O(*m* + *n*), where *m* is the length of this sequence
		///   and *n* is the length of the result.
		/// - SeeAlso: `joined()`, `map(_:)`
		public func flatMap<SegmentOfResult : Sequence>(_ transform: (Element) throws -> SegmentOfResult) rethrows -> [SegmentOfResult.Iterator.Element]
		
		/// Returns an array containing the non-`nil` results of calling the given
		/// transformation with each element of this sequence.
		///
		/// Use this method to receive an array of nonoptional values when your
		/// transformation produces an optional value.
		///
		/// In this example, note the difference in the result of using `map` and
		/// `flatMap` with a transformation that returns an optional `Int` value.
		///
		///     let possibleNumbers = ["1", "2", "three", "///4///", "5"]
		///
		///     let mapped: [Int?] = numbers.map { str in Int(str) }
		///     // [1, 2, nil, nil, 5]
		///
		///     let flatMapped: [Int] = numbers.flatMap { str in Int(str) }
		///     // [1, 2, 5]
		///
		/// - Parameter transform: A closure that accepts an element of this
		///   sequence as its argument and returns an optional value.
		/// - Returns: An array of the non-`nil` results of calling `transform`
		///   with each element of the sequence.
		///
		/// - Complexity: O(*m* + *n*), where *m* is the length of this sequence
		///   and *n* is the length of the result.
		public func flatMap<ElementOfResult>(_ transform: (Element) throws -> ElementOfResult?) rethrows -> [ElementOfResult]
	}
	
	/// Supply the default `makeIterator()` method for `Collection` models
	/// that accept the default associated `Iterator`,
	/// `IndexingIterator<Self>`.
	extension Array {
		
		/// Returns an iterator over the elements of the collection.
		public func makeIterator() -> IndexingIterator<Array<Element>>
	}
	
	/// Default implementations of core requirements
	extension Array {
		
		/// A Boolean value indicating whether the collection is empty.
		///
		/// When you need to check whether your collection is empty, use the
		/// `isEmpty` property instead of checking that the `count` property is
		/// equal to zero. For collections that don't conform to
		/// `RandomAccessCollection`, accessing the `count` property iterates
		/// through the elements of the collection.
		///
		///     let horseName = "Silver"
		///     if horseName.characters.isEmpty {
		///         print("I've been through the desert on a horse with no name.")
		///     } else {
		///         print("Hi ho, \(horseName)!")
		///     }
		///     // Prints "Hi ho, Silver!")
		///
		/// - Complexity: O(1)
		public var isEmpty: Bool { get }
		
		/// The first element of the collection.
		///
		/// If the collection is empty, the value of this property is `nil`.
		///
		///     let numbers = [10, 20, 30, 40, 50]
		///     if let firstNumber = numbers.first {
		///         print(firstNumber)
		///     }
		///     // Prints "10"
		public var first: Element? { get }
		
		/// A value less than or equal to the number of elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the length
		///   of the collection.
		public var underestimatedCount: Int { get }
		
		/// The number of elements in the collection.
		///
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the length
		///   of the collection.
		public var count: Int { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension Array {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyBidirectionalCollection<Array<Element>> { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension Array {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyCollection<Array<Element>> { get }
	}
	
	/// Augment `self` with lazy methods such as `map`, `filter`, etc.
	extension Array {
		
		/// A view onto this collection that provides lazy implementations of
		/// normally eager operations, such as `map` and `filter`.
		///
		/// Use the `lazy` property when chaining operations to prevent
		/// intermediate operations from allocating storage, or when you only
		/// need a part of the final collection to avoid unnecessary computation.
		///
		/// - See Also: `LazySequenceProtocol`, `LazyCollectionProtocol`.
		public var lazy: LazyRandomAccessCollection<Array<Element>> { get }
	}
	
	/// Default implementation for forward collections.
	extension Array {
		
		/// Offsets the given index by the specified distance.
		///
		/// The value passed as `n` must not offset `i` beyond the `endIndex` or
		/// before the `startIndex` of this collection.
		///
		/// - Parameters:
		///   - i: A valid index of the collection.
		///   - n: The distance to offset `i`. `n` must not be negative unless the
		///     collection conforms to the `BidirectionalCollection` protocol.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the absolute
		///   value of `n`.
		public func formIndex(_ i: inout Int, offsetBy n: Int)
		
		/// Offsets the given index by the specified distance, or so that it equals
		/// the given limiting index.
		///
		/// The value passed as `n` must not offset `i` beyond the `endIndex` or
		/// before the `startIndex` of this collection, unless the index passed as
		/// `limit` prevents offsetting beyond those bounds.
		///
		/// - Parameters:
		///   - i: A valid index of the collection.
		///   - n: The distance to offset `i`. `n` must not be negative unless the
		///     collection conforms to the `BidirectionalCollection` protocol.
		/// - Returns: `true` if `i` has been offset by exactly `n` steps without
		///   going beyond `limit`; otherwise, `false`. When the return value is
		///   `false`, the value of `i` is equal to `limit`.
		///
		/// - SeeAlso: `index(_:offsetBy:)`, `formIndex(_:offsetBy:limitedBy:)`
		/// - Complexity: O(1) if the collection conforms to
		///   `RandomAccessCollection`; otherwise, O(*n*), where *n* is the absolute
		///   value of `n`.
		public func formIndex(_ i: inout Int, offsetBy n: Int, limitedBy limit: Int) -> Bool
	}
	
	extension Array : CustomReflectable {
		
		/// A mirror that reflects the array.
		public var customMirror: Mirror { get }
	}
	
	extension Array : RangeReplaceableCollection {
		
		/// Creates a new, empty array.
		///
		/// This is equivalent to initializing with an empty array literal.
		/// For example:
		///
		///     var emptyArray = Array<Int>()
		///     print(emptyArray.isEmpty)
		///     // Prints "true"
		///
		///     emptyArray = []
		///     print(emptyArray.isEmpty)
		///     // Prints "true"
		public init()
		
		/// Creates an array containing the elements of a sequence.
		///
		/// You can use this initializer to create an array from any other type that
		/// conforms to the `Sequence` protocol. For example, you might want to
		/// create an array with the integers from 1 through 7. Use this initializer
		/// around a range instead of typing all those numbers in an array literal.
		///
		///     let numbers = Array(1...7)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 6, 7]"
		///
		/// You can also use this initializer to convert a complex sequence or
		/// collection type back to an array. For example, the `keys` property of
		/// a dictionary isn't an array with its own storage, it's a collection
		/// that maps its elements from the dictionary only when they're
		/// accessed, saving the time and space needed to allocate an array. If
		/// you need to pass those keys to a method that takes an array, however,
		/// use this initializer to convert that list from its type of
		/// `LazyMapCollection<Dictionary<String, Int>, Int>` to a simple
		/// `[String]`.
		///
		///     func cacheImagesWithNames(names: [String]) {
		///         // custom image loading and caching
		///      }
		///
		///     let namedHues: [String: Int] = ["Vermillion": 18, "Magenta": 302,
		///             "Gold": 50, "Cerise": 320]
		///     let colorNames = Array(namedHues.keys)
		///     cacheImagesWithNames(colorNames)
		///
		///     print(colorNames)
		///     // Prints "["Gold", "Cerise", "Magenta", "Vermillion"]"
		///
		/// - Parameter s: The sequence of elements to turn into an array.
		public init<S : Sequence where S.Iterator.Element == Element>(_ s: S)
		
		/// Creates a new array containing the specified number of a single, repeated
		/// value.
		///
		/// Here's an example of creating an array initialized with five strings
		/// containing the letter *Z*.
		///
		///     let fiveZs = Array(repeating: "Z", count: 5)
		///     print(fiveZs)
		///     // Prints "["Z", "Z", "Z", "Z", "Z"]"
		///
		/// - Parameters:
		///   - repeatedValue: The element to repeat.
		///   - count: The number of times to repeat the value passed in the
		///     `repeating` parameter. `count` must be zero or greater.
		public init(repeating repeatedValue: Element, count: Int)
		
		/// The number of elements in the array.
		public var count: Int { get }
		
		/// The total number of elements that the array can contain using its current
		/// storage.
		///
		/// If the array grows larger than its capacity, it discards its current
		/// storage and allocates a larger one.
		///
		/// The following example creates an array of integers from an array literal,
		/// then appends the elements of another collection. Before appending, the
		/// array allocates new storage that is large enough store the resulting
		/// elements.
		///
		///     var numbers = [10, 20, 30, 40, 50]
		///     print("Count: \(numbers.count), capacity: \(numbers.capacity)")
		///     // Prints "Count: 5, capacity: 5"
		///
		///     numbers.append(contentsOf: stride(from: 60, through: 100, by: 10))
		///     print("Count: \(numbers.count), capacity: \(numbers.capacity)")
		///     // Prints "Count: 10, capacity: 12"
		public var capacity: Int { get }
		
		/// Reserves enough space to store the specified number of elements.
		///
		/// If you are adding a known number of elements to an array, use this method
		/// to avoid multiple reallocations. This method ensures that the array has
		/// unique, mutable, contiguous storage, with space allocated for at least
		/// the requested number of elements.
		///
		/// For performance reasons, the newly allocated storage may be larger than
		/// the requested capacity. Use the array's `capacity` property to determine
		/// the size of the new storage.
		///
		/// - Parameter minimumCapacity: The requested number of elements to store.
		///
		/// - Complexity: O(*n*), where *n* is the count of the array.
		public mutating func reserveCapacity(_ minimumCapacity: Int)
		
		/// Adds a new element at the end of the array.
		///
		/// Use this method to append a single element to the end of a mutable array.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(100)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 100]"
		///
		/// Because arrays increase their allocated capacity using an exponential
		/// strategy, appending a single element to an array is an O(1) operation
		/// when averaged over many calls to the `append(_:)` method. When an array
		/// has additional capacity and is not sharing its storage with another
		/// instance, appending an element is O(1). When an array needs to
		/// reallocate storage before appending or its storage is shared with
		/// another copy, appending is O(*n*), where *n* is the length of the array.
		///
		/// - Parameter newElement: The element to append to the array.
		///
		/// - Complexity: Amortized O(1) over many additions. If the array uses a
		///   bridged `NSArray` instance as its storage, the efficiency is
		///   unspecified.
		public mutating func append(_ newElement: Element)
		
		/// Adds the elements of a sequence to the end of the array.
		///
		/// Use this method to append the elements of a sequence to the end of an
		/// array. This example appends the elements of a `Range<Int>` instance
		/// to an array of integers.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(contentsOf: 10...15)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
		///
		/// - Parameter newElements: The elements to append to the array.
		///
		/// - Complexity: O(*n*), where *n* is the length of the resulting array.
		public mutating func append<S : Sequence where S.Iterator.Element == Element>(contentsOf newElements: S)
		
		/// Adds the elements of a collection to the end of the array.
		///
		/// Use this method to append the elements of a collection to the end of this
		/// array. This example appends the elements of a `Range<Int>` instance
		/// to an array of integers.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.append(contentsOf: 10...15)
		///     print(numbers)
		///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
		///
		/// - Parameter newElements: The elements to append to the array.
		///
		/// - Complexity: O(*n*), where *n* is the length of the resulting array.
		public mutating func append<C : Collection where C.Iterator.Element == Element>(contentsOf newElements: C)
		
		/// Inserts a new element at the specified position.
		///
		/// The new element is inserted before the element currently at the specified
		/// index. If you pass the array's `endIndex` property as the `index`
		/// parameter, the new element is appended to the array.
		///
		///     var numbers = [1, 2, 3, 4, 5]
		///     numbers.insert(100, at: 3)
		///     numbers.insert(200, at: numbers.endIndex)
		///
		///     print(numbers)
		///     // Prints "[1, 2, 3, 100, 4, 5, 200]"
		///
		/// - Parameter newElement: The new element to insert into the array.
		/// - Parameter i: The position at which to insert the new element.
		///   `index` must be a valid index of the array or equal to its `endIndex`
		///   property.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func insert(_ newElement: Element, at i: Int)
		
		/// Removes and returns the element at the specified position.
		///
		/// All the elements following the specified position are moved up to
		/// close the gap.
		///
		///     var measurements: [Double] = [1.1, 1.5, 2.9, 1.2, 1.5, 1.3, 1.2]
		///     let removed = measurements.remove(at: 2)
		///     print(measurements)
		///     // Prints "[1.1, 1.5, 1.2, 1.5, 1.3, 1.2]"
		///
		/// - Parameter index: The position of the element to remove. `index` must
		///   be a valid index of the array.
		/// - Returns: The element at the specified index.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func remove(at index: Int) -> Element
		
		/// Removes all elements from the array.
		///
		/// - Parameter keepCapacity: Pass `true` to keep the existing capacity of
		///   the array after removing its elements. The default value is
		///   `false`.
		///
		/// - Complexity: O(*n*), where *n* is the length of the array.
		public mutating func removeAll(keepingCapacity keepCapacity: Bool = default)
	}
	
	extension Array : ExpressibleByArrayLiteral {
		
		/// Creates an array from the given array literal.
		///
		/// Do not call this initializer directly. It is used by the compiler
		/// when you use an array literal. Instead, create a new array by using an
		/// array literal as its value. To do this, enclose a comma-separated list of
		/// values in square brackets.
		///
		/// Here, an array of strings is created from an array literal holding
		/// only strings.
		///
		///     let ingredients = ["cocoa beans", "sugar", "cocoa butter", "salt"]
		///
		/// - Parameter elements: A variadic list of elements of the new array.
		public init(arrayLiteral elements: Element...)
	}
	
	extension Array : CustomStringConvertible, CustomDebugStringConvertible {
		
		/// A textual representation of the array and its elements.
		public var description: String { get }
		
		/// A textual representation of the array and its elements, suitable for
		/// debugging.
		public var debugDescription: String { get }
	}
	
	extension Array where Element : Equatable {
		
		/// Returns the longest possible subsequences of the collection, in order,
		/// around elements equal to the given element.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the collection are not returned as part
		/// of any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string at each
		/// space character (" "). The first use of `split` returns each word that
		/// was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(separator: " ")
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(line.characters.split(separator: " ", maxSplits: 1)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(separator: " ", omittingEmptySubsequences: false)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - separator: The element that should be split upon.
		///   - maxSplits: The maximum number of times to split the collection, or
		///     one less than the number of subsequences to return. If
		///     `maxSplits + 1` subsequences are returned, the last one is a suffix
		///     of the original collection containing the remaining elements.
		///     `maxSplits` must be greater than or equal to zero. The default value
		///     is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each consecutive pair of `separator`
		///     elements in the collection and for each instance of `separator` at
		///     the start or end of the collection. If `true`, only nonempty
		///     subsequences are returned. The default value is `true`.
		/// - Returns: An array of subsequences, split from this collection's
		///   elements.
		public func split(separator: Element, maxSplits: Int = default, omittingEmptySubsequences: Bool = default) -> [ArraySlice<Element>]
		
		/// Returns the first index where the specified value appears in the
		/// collection.
		///
		/// After using `index(of:)` to find the position of a particular element in
		/// a collection, you can use it to access the element by subscripting. This
		/// example shows how you can modify one of the names in an array of
		/// students.
		///
		///     var students = ["Ben", "Ivy", "Jordell", "Maxime"]
		///     if let i = students.index(of: "Maxime") {
		///         students[i] = "Max"
		///     }
		///     print(students)
		///     // Prints "["Ben", "Ivy", "Jordell", "Max"]"
		///
		/// - Parameter element: An element to search for in the collection.
		/// - Returns: The first index where `element` is found. If `element` is not
		///   found in the collection, returns `nil`.
		///
		/// - SeeAlso: `index(where:)`
		public func index(of element: Element) -> Int?
		
		/// Returns the longest possible subsequences of the sequence, in order,
		/// around elements equal to the given element.
		///
		/// The resulting array consists of at most `maxSplits + 1` subsequences.
		/// Elements that are used to split the sequence are not returned as part of
		/// any subsequence.
		///
		/// The following examples show the effects of the `maxSplits` and
		/// `omittingEmptySubsequences` parameters when splitting a string at each
		/// space character (" "). The first use of `split` returns each word that
		/// was originally separated by one or more spaces.
		///
		///     let line = "BLANCHE:   I don't want realism. I want magic!"
		///     print(line.characters.split(separator: " ")
		///                          .map(String.init))
		///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// The second example passes `1` for the `maxSplits` parameter, so the
		/// original string is split just once, into two new strings.
		///
		///     print(line.characters.split(separator: " ", maxSplits: 1)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
		///
		/// The final example passes `false` for the `omittingEmptySubsequences`
		/// parameter, so the returned array contains empty strings where spaces
		/// were repeated.
		///
		///     print(line.characters.split(separator: " ", omittingEmptySubsequences: false)
		///                           .map(String.init))
		///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
		///
		/// - Parameters:
		///   - separator: The element that should be split upon.
		///   - maxSplits: The maximum number of times to split the sequence, or one
		///     less than the number of subsequences to return. If `maxSplits + 1`
		///     subsequences are returned, the last one is a suffix of the original
		///     sequence containing the remaining elements. `maxSplits` must be
		///     greater than or equal to zero. The default value is `Int.max`.
		///   - omittingEmptySubsequences: If `false`, an empty subsequence is
		///     returned in the result for each consecutive pair of `separator`
		///     elements in the sequence and for each instance of `separator` at the
		///     start or end of the sequence. If `true`, only nonempty subsequences
		///     are returned. The default value is `true`.
		/// - Returns: An array of subsequences, split from this sequence's elements.
		public func split(separator: Element, maxSplits: Int = default, omittingEmptySubsequences: Bool = default) -> [AnySequence<Element>]
		
		/// Returns a Boolean value indicating whether the initial elements of the
		/// sequence are the same as the elements in another sequence.
		///
		/// This example tests whether one countable range begins with the elements
		/// of another countable range.
		///
		///     let a = 1...3
		///     let b = 1...10
		///
		///     print(b.starts(with: a))
		///     // Prints "true"
		///
		/// Passing an sequence with no elements or an empty collection as
		/// `possiblePrefix` always results in `true`.
		///
		///     print(b.starts(with: []))
		///     // Prints "true"
		///
		/// - Parameter possiblePrefix: A sequence to compare to this sequence.
		/// - Returns: `true` if the initial elements of the sequence are the same as
		///   the elements of `possiblePrefix`; otherwise, `false`. If
		///   `possiblePrefix` has no elements, the return value is `true`.
		///
		/// - SeeAlso: `starts(with:by:)`
		public func starts<PossiblePrefix where PossiblePrefix : Sequence, PossiblePrefix.Iterator.Element == Element>(with possiblePrefix: PossiblePrefix) -> Bool
		
		/// Returns a Boolean value indicating whether this sequence and another
		/// sequence contain the same elements in the same order.
		///
		/// At least one of the sequences must be finite.
		///
		/// This example tests whether one countable range shares the same elements
		/// as another countable range and an array.
		///
		///     let a = 1...3
		///     let b = 1...10
		///
		///     print(a.elementsEqual(b))
		///     // Prints "false"
		///     print(a.elementsEqual([1, 2, 3]))
		///     // Prints "true"
		///
		/// - Parameter other: A sequence to compare to this sequence.
		/// - Returns: `true` if this sequence and `other` contain the same elements
		///   in the same order.
		///
		/// - SeeAlso: `elementsEqual(_:by:)`
		public func elementsEqual<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence) -> Bool
	}
	
	extension Array where Element == String {
		
		/// Returns a new string by concatenating the elements of the sequence,
		/// adding the given separator between each element.
		///
		/// The following example shows how an array of strings can be joined to a
		/// single, comma-separated string:
		///
		///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
		///     let list = cast.joined(separator: ", ")
		///     print(list)
		///     // Prints "Vivien, Marlon, Kim, Karl"
		///
		/// - Parameter separator: A string to insert between each of the elements
		///   in this sequence. The default separator is an empty string.
		/// - Returns: A single, concatenated string.
		public func joined(separator: String = default) -> String
	}
	
	extension Array where Element : Collection {
		
		/// Returns the elements of this collection of collections, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   collection of collections.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenCollection<Array<Element>>
	}
	
	extension Array where Element : BidirectionalCollection {
		
		/// Returns the elements of this collection of collections, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   collection of collections.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenBidirectionalCollection<Array<Element>>
	}
	
	extension Array where Element : Sequence {
		
		/// Returns the elements of this sequence of sequences, concatenated.
		///
		/// In this example, an array of three ranges is flattened so that the
		/// elements of each range can be iterated in turn.
		///
		///     let ranges = [0..<3, 8..<10, 15..<17]
		///
		///     // A for-in loop over 'ranges' accesses each range:
		///     for range in ranges {
		///       print(range)
		///     }
		///     // Prints "0..<3"
		///     // Prints "8..<10"
		///     // Prints "15..<17"
		///
		///     // Use 'joined()' to access each element of each range:
		///     for index in ranges.joined() {
		///         print(index, terminator: " ")
		///     }
		///     // Prints: "0 1 2 8 9 15 16"
		///
		/// - Returns: A flattened view of the elements of this
		///   sequence of sequences.
		///
		/// - SeeAlso: `flatMap(_:)`, `joined(separator:)`
		public func joined() -> FlattenSequence<Array<Element>>
		
		/// Returns the concatenated elements of this sequence of sequences,
		/// inserting the given separator between each element.
		///
		/// This example shows how an array of `[Int]` instances can be joined, using
		/// another `[Int]` instance as the separator:
		///
		///     let nestedNumbers = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
		///     let joined = nestedNumbers.joined(separator: [-1, -2])
		///     print(Array(joined))
		///     // Prints "[1, 2, 3, -1, -2, 4, 5, 6, -1, -2, 7, 8, 9]"
		///
		/// - Parameter separator: A sequence to insert between each of this
		///   sequence's elements.
		/// - Returns: The joined sequence of elements.
		///
		/// - SeeAlso: `joined()`
		public func joined<Separator : Sequence where Separator.Iterator.Element == Iterator.Element.Iterator.Element>(separator: Separator) -> JoinedSequence<Array<Element>>
	}
	
	extension Array where Element : Comparable {
		
		/// Returns the elements of the sequence, sorted.
		///
		/// You can sort any sequence of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let sortedStudents = students.sorted()
		///     print(sortedStudents)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your sequence in descending order, pass the
		/// greater-than operator (`>`) to the `sorted(by:)` method.
		///
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Returns: A sorted array of the sequence's elements.
		///
		/// - SeeAlso: `sorted(by:)`
		///
		public func sorted() -> [Element]
		
		/// Returns the elements of the collection, sorted.
		///
		/// You can sort any collection of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     let students: Set = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     let sortedStudents = students.sorted()
		///     print(sortedStudents)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your collection in descending order, pass the
		/// greater-than operator (`>`) to the `sorted(by:)` method.
		///
		///     let descendingStudents = students.sorted(by: >)
		///     print(descendingStudents)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		///
		/// - Returns: A sorted array of the collection's elements.
		///
		/// - SeeAlso: `sorted(by:)`
		/// - MutatingVariant: sort
		public func sorted() -> [Element]
		
		/// Sorts the collection in place.
		///
		/// You can sort any mutable collection of elements that conform to the
		/// `Comparable` protocol by calling this method. Elements are sorted in
		/// ascending order.
		///
		/// The sorting algorithm is not stable. A nonstable sort may change the
		/// relative order of elements that compare equal.
		///
		/// Here's an example of sorting a list of students' names. Strings in Swift
		/// conform to the `Comparable` protocol, so the names are sorted in
		/// ascending order according to the less-than operator (`<`).
		///
		///     var students = ["Kofi", "Abena", "Peter", "Kweku", "Akosua"]
		///     students.sort()
		///     print(students)
		///     // Prints "["Abena", "Akosua", "Kofi", "Kweku", "Peter"]"
		///
		/// To sort the elements of your collection in descending order, pass the
		/// greater-than operator (`>`) to the `sort(by:)` method.
		///
		///     students.sort(by: >)
		///     print(students)
		///     // Prints "["Peter", "Kweku", "Kofi", "Akosua", "Abena"]"
		public mutating func sort()
		
		/// Returns the minimum element in the sequence.
		///
		/// This example finds the smallest value in an array of height measurements.
		///
		///     let heights = [67.5, 65.7, 64.3, 61.1, 58.5, 60.3, 64.9]
		///     let lowestHeight = heights.min()
		///     print(lowestHeight)
		///     // Prints "Optional(58.5)"
		///
		/// - Returns: The sequence's minimum element. If the sequence has no
		///   elements, returns `nil`.
		///
		/// - SeeAlso: `min(by:)`
		@warn_unqualified_access
		public func min() -> Element?
		
		/// Returns the maximum element in the sequence.
		///
		/// This example finds the smallest value in an array of height measurements.
		///
		///     let heights = [67.5, 65.7, 64.3, 61.1, 58.5, 60.3, 64.9]
		///     let greatestHeight = heights.max()
		///     print(greatestHeight)
		///     // Prints "Optional(67.5)"
		///
		/// - Returns: The sequence's maximum element. If the sequence has no
		///   elements, returns `nil`.
		///
		/// - SeeAlso: `max(by:)`
		@warn_unqualified_access
		public func max() -> Element?
		
		/// Returns a Boolean value indicating whether the sequence precedes another
		/// sequence in a lexicographical (dictionary) ordering, using the
		/// less-than operator (`<`) to compare elements.
		///
		/// This example uses the `lexicographicallyPrecedes` method to test which
		/// array of integers comes first in a lexicographical ordering.
		///
		///     let a = [1, 2, 2, 2]
		///     let b = [1, 2, 3, 4]
		///
		///     print(a.lexicographicallyPrecedes(b))
		///     // Prints "true"
		///     print(b.lexicographicallyPrecedes(b))
		///     // Prints "false"
		///
		/// - Parameter other: A sequence to compare to this sequence.
		/// - Returns: `true` if this sequence precedes `other` in a dictionary
		///   ordering; otherwise, `false`.
		///
		/// - Note: This method implements the mathematical notion of lexicographical
		///   ordering, which has no connection to Unicode.  If you are sorting
		///   strings to present to the end user, use `String` APIs that
		///   perform localized comparison.
		/// - SeeAlso: `lexicographicallyPrecedes(_:by:)`
		public func lexicographicallyPrecedes<OtherSequence where OtherSequence : Sequence, OtherSequence.Iterator.Element == Element>(_ other: OtherSequence) -> Bool
	}
	
	/// Appends the elements of a sequence to a `ContiguousArray` instance.
	///
	/// Use this operator to append the elements of a sequence to the end of
	/// a `ContiguousArray` instance with same `Element` type. This example appends
	/// the elements of a `Range<Int>` instance to an array of integers.
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     numbers += 10...15
	///     print(numbers)
	///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
	///
	/// - Parameters:
	///   - lhs: The array to append to.
	///   - rhs: A collection or finite sequence.
	///
	/// - Complexity: O(*n*), where *n* is the length of the resulting array.
	public func +=<S : Sequence>(lhs: inout ContiguousArray<S.Iterator.Element>, rhs: S)
	
	/// Appends the elements of a collection to a `ContiguousArray` instance.
	///
	/// Use this operator to append the elements of a collection to the end of
	/// a `ContiguousArray` instance with same `Element` type. This example appends
	/// the elements of a `Range<Int>` instance to an array of integers.
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     numbers += 10...15
	///     print(numbers)
	///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
	///
	/// - Parameters:
	///   - lhs: The array to append to.
	///   - rhs: A collection.
	///
	/// - Complexity: O(*n*), where *n* is the length of the resulting array.
	public func +=<C : Collection>(lhs: inout ContiguousArray<C.Iterator.Element>, rhs: C)
	
	/// Appends the elements of a sequence to an `ArraySlice` instance.
	///
	/// Use this operator to append the elements of a sequence to the end of
	/// an `ArraySlice` instance with same `Element` type. This example appends
	/// the elements of a `Range<Int>` instance to an array of integers.
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     numbers += 10...15
	///     print(numbers)
	///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
	///
	/// - Parameters:
	///   - lhs: The array to append to.
	///   - rhs: A collection or finite sequence.
	///
	/// - Complexity: O(*n*), where *n* is the length of the resulting array.
	public func +=<S : Sequence>(lhs: inout ArraySlice<S.Iterator.Element>, rhs: S)
	
	/// Appends the elements of a collection to an `ArraySlice` instance.
	///
	/// Use this operator to append the elements of a collection to the end of
	/// an `ArraySlice` instance with same `Element` type. This example appends
	/// the elements of a `Range<Int>` instance to an array of integers.
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     numbers += 10...15
	///     print(numbers)
	///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
	///
	/// - Parameters:
	///   - lhs: The array to append to.
	///   - rhs: A collection.
	///
	/// - Complexity: O(*n*), where *n* is the length of the resulting array.
	public func +=<C : Collection>(lhs: inout ArraySlice<C.Iterator.Element>, rhs: C)
	
	/// Appends the elements of a sequence to an array.
	///
	/// Use this operator to append the elements of a sequence to the end of
	/// an array with same `Element` type. This example appends
	/// the elements of a `Range<Int>` instance to an array of integers.
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     numbers += 10...15
	///     print(numbers)
	///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
	///
	/// - Parameters:
	///   - lhs: The array to append to.
	///   - rhs: A collection or finite sequence.
	///
	/// - Complexity: O(*n*), where *n* is the length of the resulting array.
	public func +=<S : Sequence>(lhs: inout [S.Iterator.Element], rhs: S)
	
	/// Appends the elements of a collection to an array.
	///
	/// Use this operator to append the elements of a collection to the end of
	/// an array with same `Element` type. This example appends
	/// the elements of a `Range<Int>` instance to an array of integers.
	///
	///     var numbers = [1, 2, 3, 4, 5]
	///     numbers += 10...15
	///     print(numbers)
	///     // Prints "[1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15]"
	///
	/// - Parameters:
	///   - lhs: The array to append to.
	///   - rhs: A collection.
	///
	/// - Complexity: O(*n*), where *n* is the length of the resulting array.
	public func +=<C : Collection>(lhs: inout [C.Iterator.Element], rhs: C)
	
	/// Returns `true` if these arrays contain the same elements.
	public func ==<Element : Equatable>(lhs: ContiguousArray<Element>, rhs: ContiguousArray<Element>) -> Bool
	
	/// Returns `true` if the arrays do not contain the same elements.
	public func !=<Element : Equatable>(lhs: ContiguousArray<Element>, rhs: ContiguousArray<Element>) -> Bool
	
	/// Returns `true` if these arrays contain the same elements.
	public func ==<Element : Equatable>(lhs: ArraySlice<Element>, rhs: ArraySlice<Element>) -> Bool
	
	/// Returns `true` if the arrays do not contain the same elements.
	public func !=<Element : Equatable>(lhs: ArraySlice<Element>, rhs: ArraySlice<Element>) -> Bool
	
	/// Returns `true` if these arrays contain the same elements.
	public func ==<Element : Equatable>(lhs: [Element], rhs: [Element]) -> Bool
	
	/// Returns `true` if the arrays do not contain the same elements.
	public func !=<Element : Equatable>(lhs: [Element], rhs: [Element]) -> Bool
	
	/// Append the elements of `rhs` to `lhs`.
	public func +=<Element, C : Collection where C.Iterator.Element == Element>(lhs: inout _ContiguousArrayBuffer<Element>, rhs: C)
	


#endif /* jr_array_h */
